#include "gueepo2Dpch.h"
#include "Renderer.h"
#include "core/renderer/VertexArray.h"
#include "core/renderer/OrtographicCamera.h"
#include "core/renderer/Texture.h"

namespace gueepo {

	struct QuadVertex {
		gueepo::math::Vector3 Position;
		gueepo::math::Vector2 TexCoord;
		float TextureSlot = 0.0f;
	};

	static struct {
		// Camera Data
		math::Matrix4 ViewProjection;

		// Maximum
		static const uint32_t MaxQuads = 1000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 16;

		// Defaults
		Shader* defaultSpriteShader = nullptr;
		VertexBuffer* defaultVertexBuffer = nullptr;
		VertexArray* defaultVertexArray = nullptr;
		math::Vector3 quadVertexPosition[4];

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

	void Renderer::Initialize() {
		s_RenderData.defaultVertexArray = VertexArray::Create();
		s_RenderData.defaultVertexBuffer = VertexBuffer::Create(s_RenderData.MaxVertices * sizeof(QuadVertex));
		s_RenderData.defaultVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoords" },
			{ ShaderDataType::Float, "a_TextureSlot" }
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

		RenderCommand::SetClearColor(
			sceneCamera.GetBackGroundColor().rgba[0],
			sceneCamera.GetBackGroundColor().rgba[1],
			sceneCamera.GetBackGroundColor().rgba[2],
			sceneCamera.GetBackGroundColor().rgba[3]
		);
		RenderCommand::Clear();
		
		s_RenderData.RenderStats.DrawCalls = 0;
		StartBatch();
	}

	void Renderer::StartBatch() {
		s_RenderData.TextureSlotIndex = 0;
		s_RenderData.quadIndexCount = 0;
		s_RenderData.quadVertexPtrPosition = s_RenderData.quadVertexBase;
	}

	void Renderer::NextBatch() {
		LOG_INFO("more quads or more textures than the maximum! flushing and starting a new batch!");
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
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Draw(const math::Matrix4& transform, const math::Vector2& textureCoordMin, const math::Vector2& textureCoordMax, Texture* texture) {

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

		math::Vector2 textureCoords[] = {
			{ textureCoordMin.x, textureCoordMin.y },
			{ textureCoordMax.x, textureCoordMin.y },
			{ textureCoordMax.x, textureCoordMax.y },
			{ textureCoordMin.x, textureCoordMax.y }
		};

		for (size_t i = 0; i < quadVertexCount; i++) {
			s_RenderData.quadVertexPtrPosition->Position = transform * s_RenderData.quadVertexPosition[i];
			s_RenderData.quadVertexPtrPosition->TexCoord = textureCoords[i];
			s_RenderData.quadVertexPtrPosition->TextureSlot = textureSlot;
			s_RenderData.quadVertexPtrPosition++;
		}

		s_RenderData.quadIndexCount += 6;
	}

	void Renderer::Draw(const math::Matrix4 & transform, Texture * texture) {
		Draw(transform, math::Vector2(0.0f), math::Vector2(1.0f), texture);
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
		RenderCommand::DrawIndexed(s_RenderData.defaultVertexArray, s_RenderData.quadIndexCount);
		s_RenderData.RenderStats.DrawCalls++;
	}

}