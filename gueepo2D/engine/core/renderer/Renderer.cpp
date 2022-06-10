#include "gueepo2Dpch.h"
#include "Renderer.h"
#include "core/renderer/VertexArray.h"
#include "core/renderer/OrtographicCamera.h"
#include "core/renderer/Texture.h"
#include "FontSprite.h"

// Specific Renderer APIs
#include "platform/OpenGL/OpenGLRendererAPI.h"

namespace gueepo {

	static RendererAPI* s_RendererAPI = nullptr;

	static RendererAPI* InitRendererAPI() {
		
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
			LOG_ERROR("RENDERER API 'NONE' NOT IMPLEMENTED!");
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLRendererAPI();
			break;
		case RendererAPI::API::DirectX:
		case RendererAPI::API::Vulkan:
		case RendererAPI::API::Metal:
			LOG_ERROR("RENDERER API NOT IMPLEMENTED!");
			break;
			
		}

		return nullptr;
	}

	struct QuadVertex {
		gueepo::math::vec3 Position;
		gueepo::math::vec2 TexCoord;
		float TextureSlot = 0.0f;
		gueepo::Color color;
	};


	// ========================================================================
	// ========================================================================
	static struct {
		// Camera Data
		math::mat4 ViewProjection;

		// Maximum
		static const uint32_t MaxQuads = 1000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 16;

		// Defaults
		Shader* defaultSpriteShader = nullptr;
		VertexBuffer* defaultVertexBuffer = nullptr;
		VertexArray* defaultVertexArray = nullptr;
		math::vec3 quadVertexPosition[4];

		std::array<Texture*, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 0;
		
		// quad vertex counting
		uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBase = nullptr;
		QuadVertex* quadVertexPtrPosition = nullptr;

		struct {
			uint32_t DrawCalls;
		} RenderStats = { 0 };
	} s_RenderData;

	int Renderer::GetDrawCalls() {
		return s_RenderData.RenderStats.DrawCalls;
	}

	void Renderer::Initialize() {
		
		s_RendererAPI = InitRendererAPI();

		if (s_RendererAPI == nullptr) {
			LOG_ERROR("Error initializing Renderer API");
			return;
		}

		LOG_INFO("quad vertex size: {0}", sizeof QuadVertex);
		LOG_INFO("sizeof color class: {0}", sizeof Color);

		s_RenderData.defaultVertexArray = VertexArray::Create();
		s_RenderData.defaultVertexBuffer = VertexBuffer::Create(s_RenderData.MaxVertices * sizeof(QuadVertex));
		s_RenderData.defaultVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoords" },
			{ ShaderDataType::Float, "a_TextureSlot" },
			{ ShaderDataType::Float4, "a_Color "}
		});
		s_RenderData.defaultVertexArray->AddVertexBuffer(s_RenderData.defaultVertexBuffer);
		
		s_RenderData.quadVertexBase = new QuadVertex[s_RenderData.MaxVertices];
		uint32_t* quadIndices = new uint32_t[s_RenderData.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_RenderData.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			offset += 4;
		}

		IndexBuffer* quadIndexBuffer = IndexBuffer::Create(quadIndices, s_RenderData.MaxIndices);
		s_RenderData.defaultVertexArray->SetIndexBuffer(quadIndexBuffer);
		delete[] quadIndices;

		// #todo: well, ideally we should have a default assets folder or some way that we know this is not going to break, lmao.
		s_RenderData.defaultSpriteShader = Shader::CreateFromFile("./assets/shaders/sprite.vertex", "./assets/shaders/sprite.fragment");

		s_RenderData.quadVertexPosition[0] = { -0.5f, -0.5f, 0.0f };
		s_RenderData.quadVertexPosition[1] = {  0.5f, -0.5f, 0.0f };
		s_RenderData.quadVertexPosition[2] = {  0.5f,  0.5f, 0.0f };
		s_RenderData.quadVertexPosition[3] = { -0.5f,  0.5f, 0.0f };
	}

	void Renderer::Shutdown() {
		delete[] s_RenderData.quadVertexBase;

	}

	void Renderer::BeginScene(OrtographicCamera& sceneCamera) {
		s_RenderData.ViewProjection = sceneCamera.GetViewProjectionMatrix();

		s_RendererAPI->SetClearColor(
			sceneCamera.GetBackGroundColor().rgba[0],
			sceneCamera.GetBackGroundColor().rgba[1],
			sceneCamera.GetBackGroundColor().rgba[2],
			sceneCamera.GetBackGroundColor().rgba[3]
		);
		s_RendererAPI->Clear();
		
		s_RenderData.RenderStats.DrawCalls = 0;
		StartBatch();
	}

	void Renderer::StartBatch() {
		s_RenderData.TextureSlotIndex = 0;
		s_RenderData.quadIndexCount = 0;
		s_RenderData.quadVertexPtrPosition = s_RenderData.quadVertexBase;
	}

	void Renderer::NextBatch() {
		// LOG_INFO("more quads or more textures than the maximum! flushing and starting a new batch!");
		Flush();
		StartBatch();
	}

	void Renderer::EndScene() {
		Flush();
	}

	void Renderer::Submit(VertexArray* vertexArray, Shader* shader) {
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_RenderData.ViewProjection);
		vertexArray->Bind();
		s_RendererAPI->DrawIndexed(vertexArray);
	}

	void Renderer::SetUnpackAlignment(int value) {
		s_RendererAPI->SetUnpackAlignment(value);
	}

	void Renderer::Draw(const math::mat4& transform, const math::vec2& textureCoordMin, const math::vec2& textureCoordMax, Texture* texture, Color color) {

		if (
			s_RenderData.quadIndexCount >= s_RenderData.MaxIndices ||
			s_RenderData.TextureSlotIndex >= s_RenderData.MaxTextureSlots
			) {
			NextBatch();
		}

		float textureSlot = -1.0f;

		// searching for the texture on the array
		for (size_t i = 0; i < s_RenderData.TextureSlotIndex; i++) {
			if (s_RenderData.TextureSlots[i] == texture) {
				textureSlot = (float)i;
				break;
			}
		}

		// if we didn't find it, we add it.
		if (textureSlot == -1.0f) {
			// #todo: check if we are not over the maximum texture slots, if we are we have to flush
			textureSlot = (float)s_RenderData.TextureSlotIndex;
			s_RenderData.TextureSlots[s_RenderData.TextureSlotIndex] = texture;
			s_RenderData.TextureSlotIndex++;
		}

		size_t quadVertexCount = 4;

		math::vec2 textureCoords[] = {
			{ textureCoordMin.x, textureCoordMin.y },
			{ textureCoordMax.x, textureCoordMin.y },
			{ textureCoordMax.x, textureCoordMax.y },
			{ textureCoordMin.x, textureCoordMax.y }
		};

		for (size_t i = 0; i < quadVertexCount; i++) {
			s_RenderData.quadVertexPtrPosition->Position = transform * s_RenderData.quadVertexPosition[i];
			s_RenderData.quadVertexPtrPosition->TexCoord = textureCoords[i];
			s_RenderData.quadVertexPtrPosition->TextureSlot = textureSlot;
			s_RenderData.quadVertexPtrPosition->color = color;
			s_RenderData.quadVertexPtrPosition++;
		}

		s_RenderData.quadIndexCount += 6;
	}

	void Renderer::Draw(const math::mat4& transform, const math::vec2& textureCoordMin, const math::vec2& textureCoordMax, Texture* texture) {
		Draw(transform, textureCoordMin, textureCoordMax, texture, Color(1.0f, 1.0f, 1.0f, 1.0f));
	}

	void Renderer::Draw(const math::mat4 & transform, Texture * texture) {
		Draw(transform, math::vec2(0.0f), math::vec2(1.0f), texture);
	}

	void Renderer::Draw(const math::vec2& position, Texture* texture) {
		math::mat4 transformMatrix = math::mat4::CreateScale(math::vec2(static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()))) * math::mat4::CreateTranslation(position);
		Draw(transformMatrix * math::mat4::m4Identity, math::vec2::Zero, math::vec2::One, texture);
	}

	void Renderer::Draw(Texture* texture) {
		Draw(math::vec2::Zero, texture);
	}


	void Renderer::DrawText(FontSprite* fontSprite, gueepo::string text, const math::vec2& position, float scale, Color color) {
		
		math::vec2 offset = math::vec2(0, 0);
		uint32_t last = 0;

		for (int i = 0, l = text.length(); i < l; i += text.utf8_length(i)) {
			uint32_t next = text.utf8_at(i);

			if (next == '\n') {
				offset.x = 0;
				offset.y -= fontSprite->lineHeight();
				last = 0;
				continue;
			}

			const SpriteCharacter& ch = fontSprite->GetSpriteCharacter(next);
			if (ch.texture != nullptr) {
				math::vec2 at = offset + ch.bearing;
				at.x += ch.size.x / 2.0f;
				at.y = offset.y;
				at.y += ch.size.y / 2.0f;
				at.y += ch.bearing.y;

				if (i > 0 && text[i - 1] != '\n') {
					at.x += fontSprite->kerning(last, next);
				}

				math::mat4 transformMatrix =
					math::mat4::CreateScale(ch.size) *
					math::mat4::CreateScale(math::vec2(scale, scale)) *
					math::mat4::CreateTranslation(position + at);

				Draw(transformMatrix, math::vec2::Zero, math::vec2::One, ch.texture, color);
			}

			offset.x += ch.advance;
			last = next;
		}
	}

	void Renderer::Flush() {
		uint32_t dataSize = (uint32_t)((uint8_t*)s_RenderData.quadVertexPtrPosition - (uint8_t*)s_RenderData.quadVertexBase);
		s_RenderData.defaultVertexBuffer->SetData(s_RenderData.quadVertexBase, dataSize);

		// binding all textures
		for (uint32_t i = 0; i < s_RenderData.TextureSlotIndex; i++) {
			s_RenderData.TextureSlots[i]->Bind(i);
		}

		s_RenderData.defaultSpriteShader->Bind();
		s_RenderData.defaultSpriteShader->SetMat4("u_ViewProjection", s_RenderData.ViewProjection);
		s_RenderData.defaultVertexArray->Bind();
		s_RendererAPI->DrawIndexed(s_RenderData.defaultVertexArray, s_RenderData.quadIndexCount);
		s_RenderData.RenderStats.DrawCalls++;
	}

}