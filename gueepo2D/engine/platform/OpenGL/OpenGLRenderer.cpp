#include "OpenGLRenderer.h"

#include "core/renderer/OrtographicCamera.h"
#include "core/renderer/FontSprite.h"

#include "platform/OpenGL/OpenGLTexture.h"

#include "platform/OpenGL/OpenGLMaterial.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLVertexBuffer.h"
#include "platform/OpenGL/OpenGLVertexArray.h"
#include "platform/OpenGL/OpenGLIndexBuffer.h"
#include <SDL.h>
#include <glad/glad.h>

const char* spriteVertexShader =
#ifdef __EMSCRIPTEN__
    "#version 300 es\n"
#else
	"#version 330 core\n"
#endif
	"layout(location = 0) in vec3 a_Position;\n"
	"layout(location = 1) in vec2 a_TexCoord;\n"
	"layout(location = 2) in float a_TextureSlot;\n"
	"layout(location = 3) in vec4 a_Color;\n"
	"layout(location = 4) in float a_ShaderType;\n"
	"\n"
	"uniform mat4 u_ViewProjection;\n"
	"\n"
	"out vec3 v_Position;\n"
	"out vec2 v_TexCoord;\n"
	"out float v_TextureSlot;\n"
	"out vec4 v_Color;\n"
	"out float v_ShaderType;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);\n"
	"	v_TexCoord = a_TexCoord;\n"
	"	v_TextureSlot = a_TextureSlot;\n"
	"	v_Color = a_Color;\n"
	"	v_ShaderType = a_ShaderType;\n"
	"}\n";

#ifdef __EMSCRIPTEN__
const char* spriteFragmentShader =
        "#version 300 es\n"
        "precision mediump float;\n"
        "\n"
        "out vec4 v_FragColor;\n"
        "\n"
        "in vec2 v_TexCoord;\n"
        "in float v_TextureSlot;\n"
        "in vec4 v_Color;\n"
        "in float v_ShaderType;\n"
        "\n"
        "uniform sampler2D u_textureSampler[16];\n"
        "\n"
        "void main()\n"
        "{\n"
        "	int index = int(v_TextureSlot);\n"
        "	float shaderType = v_ShaderType;\n"
        "\n"
        "	if (shaderType == 1.0) {\n"
        "       vec4 color = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "       if(index == 0) {\n"
        "           color = texture(u_textureSampler[0], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 1) {\n"
        "           color = texture(u_textureSampler[1], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 2) {\n"
        "           color = texture(u_textureSampler[2], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 3) {\n"
        "           color = texture(u_textureSampler[3], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 4) {\n"
        "           color = texture(u_textureSampler[4], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 5) {\n"
        "           color = texture(u_textureSampler[5], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 6) {\n"
        "           color = texture(u_textureSampler[6], v_TexCoord);\n"
        "       }\n"
        "       else  if(index == 7) {\n"
        "           color = texture(u_textureSampler[7], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 8) {\n"
        "           color = texture(u_textureSampler[8], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 9) {\n"
        "           color = texture(u_textureSampler[9], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 10) {\n"
        "           color = texture(u_textureSampler[10], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 11) {\n"
        "           color = texture(u_textureSampler[11], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 12) {\n"
        "           color = texture(u_textureSampler[12], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 13) {\n"
        "           color = texture(u_textureSampler[13], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 14) {\n"
        "           color = texture(u_textureSampler[14], v_TexCoord);\n"
        "       }\n"
        "       else if(index == 15) {\n"
        "           color = texture(u_textureSampler[15], v_TexCoord);\n"
        "       }\n"
        "		v_FragColor = v_Color * color;\n"
        "	}\n"
        "	else if (shaderType == 2.0) {\n"
        "       vec4 color = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "       if(index == 0) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[0], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 1) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[1], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 2) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[2], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 3) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[3], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 4) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[4], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 5) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[5], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 6) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[6], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 7) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[7], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 8) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[8], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 9) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[9], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 10) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[10], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 11) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[11], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 12) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[12], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 13) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[13], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 14) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[14], v_TexCoord).r);\n"
        "       }\n"
        "       else if(index == 15) {\n"
        "           color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[15], v_TexCoord).r);\n"
        "       }\n"
        "		v_FragColor = vec4(v_Color.xyz, 1.0) * color;\n"
        "	}\n"
        "	else {\n"
        "		// let's put an annoying color here so there's clearly something wrong.\n"
        "		v_FragColor = vec4(1.0, v_ShaderType, 0.0, 1.0);\n"
        "	}\n"
        "}\n";
#else
const char* spriteFragmentShader =
        "#version 330 core\n"
        "\n"
        "out vec4 v_FragColor;\n"
        "\n"
        "in vec2 v_TexCoord;\n"
        "in float v_TextureSlot;\n"
        "in vec4 v_Color;\n"
        "in float v_ShaderType;\n"
        "\n"
        "uniform sampler2D u_textureSampler[16];\n"
        "\n"
        "void main()\n"
        "{\n"
        "	int index = int(v_TextureSlot);\n"
        "	float shaderType = v_ShaderType;\n"
        "\n"
        "	if (shaderType == 1.0) {\n"
        "		vec4 color = texture(u_textureSampler[index], v_TexCoord);\n"
        "		v_FragColor = v_Color * color;\n"
        "	}\n"
        "	else if (shaderType == 2.0) {\n"
        "		vec4 color = vec4(1.0, 1.0, 1.0, texture(u_textureSampler[index], v_TexCoord).r);\n"
        "		v_FragColor = vec4(v_Color.xyz, 1.0) * color;\n"
        "	}\n"
        "	else {\n"
        "		// let's put an annoying color here so there's clearly something wrong.\n"
        "		v_FragColor = vec4(1.0, v_ShaderType, 0.0, 1.0);\n"
        "	}\n"
        "}\n";
#endif

namespace gueepo {

	void OpenGLRenderer::Initialize_Internal() {
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			LOG_ERROR("unable to initialize glad! {0}", glGetError());
		}

		glGetError();

		// (1) Initializing Shader.
		m_shader = new OpenGLShader(spriteVertexShader, spriteFragmentShader);

		// (1.5) Initializing our material
		m_material = new OpenGLMaterial(m_shader);
		m_material->SetupTextureSamplerArray("u_textureSampler", RenderData::MaxTextureSlots);

		// (2) Initializing Buffers
		m_vertexArray = new OpenGLVertexArray();
		m_vertexBuffer = new OpenGLVertexBuffer(RenderData::MaxVertices * sizeof(QuadVertex));
		m_vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoords" },
			{ ShaderDataType::Float, "a_TextureSlot" },
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float,  "a_ShaderType" }
			});
		m_vertexArray->AddVertexBuffer(m_vertexBuffer);

		uint32_t* quadIndices = new uint32_t[RenderData::MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < RenderData::MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			offset += 4;
		}

		OpenGLIndexBuffer* quadIndexBuffer = new OpenGLIndexBuffer(quadIndices, RenderData::MaxIndices);
		m_vertexArray->SetIndexBuffer(quadIndexBuffer);
		delete[] quadIndices;

		LOG_INFO("OpenGL version: {0}", glGetString(GL_VERSION));
		LOG_INFO("OpenGL vendor: {0}", glGetString(GL_VENDOR));
		LOG_INFO("OpenGL renderer: {0}", glGetString(GL_RENDERER));

		LOG_INFO("OpenGL: Initializing Sprite Batcher");
		LOG_INFO("Quad Vertex Size: {0}", sizeof(QuadVertex));
		LOG_INFO("sizeof Color Class: {0}", sizeof(Color));

		m_renderData.quadVertexBase = new QuadVertex[m_renderData.MaxVertices];
		m_renderData.quadVertexPosition[0] = { -0.5f, -0.5f, 0.0f };
		m_renderData.quadVertexPosition[1] = { 0.5f, -0.5f, 0.0f };
		m_renderData.quadVertexPosition[2] = { 0.5f,  0.5f, 0.0f };
		m_renderData.quadVertexPosition[3] = { -0.5f,  0.5f, 0.0f };
		m_isBatcherInitialized = true;
	}

	void OpenGLRenderer::Shutdown_Internal()
	{
		delete[] m_renderData.quadVertexBase;
	}

	void OpenGLRenderer::SetClearColor(const math::vec3& color) {
		glClearColor(color.x, color.y, color.z, 1.0);
	}

	void OpenGLRenderer::SetClearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void OpenGLRenderer::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	std::string OpenGLRenderer::GraphicsContextString_Internal() {
		std::string version = std::string((const char*)glGetString(GL_VERSION));
		std::string versionNumbersOnly = version.substr(0, version.find(' '));

		return "OpenGL " + std::string((const char*)glGetString(GL_VENDOR)) + " " + versionNumbersOnly;
	}

	void OpenGLRenderer::SetUnpackAlignment_Internal(int value) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, value);
	}

	void OpenGLRenderer::BeginFrame_Internal(const OrtographicCamera& camera) {
		m_renderData.ViewProjection = camera.GetViewProjectionMatrix();
		m_renderData.RenderStats.DrawCalls = 0;
		StartBatch();
	}

	void OpenGLRenderer::Draw_Internal(Texture* texture, const math::mat4& transform, const math::vec2& texCoordMin, const math::vec2& texCoordMax, Color color) {
		Draw(texture, transform, texCoordMin, texCoordMax, color, 1.0f);
	}

	void OpenGLRenderer::DrawString_Internal(FontSprite* fontSprite, gueepo::string text, const math::vec2& position, float scale, Color color) {
		math::vec2 offset = math::vec2(0, 0);
		uint32_t last = 0;

		for (int i = 0, l = text.length(); i < l; i += text.utf8_length(i)) {
			uint32_t next = text.utf8_at(i);

			if (next == '\n') {
				offset.x = 0;
				offset.y += fontSprite->lineHeight(); // adding here because down there we are going to reverse it
				last = 0;
				continue;
			}

			const SpriteCharacter& ch = fontSprite->GetSpriteCharacter(next);
			if (ch.texture != nullptr) {
				math::vec2 at = offset + ch.bearing;
				at.x += ch.size.x / 2.0f;
				at.y += ch.size.y / 2.0f;

				if (i > 0 && text[i - 1] != '\n') {
					at.x += fontSprite->kerning(last, next);
				}

				// WE HAVE TO DO -AT.Y HERE BECAUSE WE DO -SCALE DOWN THERE
				// BECAUSE IN THE ORIGINAL FONT/TEXTURE, THE CHARACTERS ARE UPSIDE DOWN
				// SO THE BEARING AND OFFSET ARE FOR THAT OCCASION
				// SO BECAUSE WE INVERSING THE SCALE, WE HAVE TO INVERSE THE BEARING/OFFSET AS WELL!!
				at.y = -at.y;

				math::mat4 transformMatrix =
					math::mat4::CreateScale(ch.size) *
					math::mat4::CreateScale(math::vec2(scale, -scale)) *
					math::mat4::CreateTranslation(position + math::vec2(at.x, at.y));

				Draw(ch.texture, transformMatrix, math::vec2::Zero, math::vec2::One, color, 2.0f);
			}

			offset.x += ch.advance;
			last = next;
		}
	}

	void OpenGLRenderer::EndFrame_Internal() {
		Flush();
	}

	// ====================================================================================
	// Private Members
	// ====================================================================================
	void OpenGLRenderer::SetBufferData(const void* data, uint32_t size) {
		m_vertexBuffer->SetData(data, size);
	}

	void OpenGLRenderer::DrawIndexed(math::mat4 viewProjectionMatrix) {
		m_material->Set("u_ViewProjection", viewProjectionMatrix);
		m_material->Bind();
		m_vertexArray->Bind();

		glDrawElements(
			GL_TRIANGLES,
			m_vertexArray->GetIndexBuffer()->GetCount(),
			GL_UNSIGNED_INT,
			nullptr
		);
	}

	void OpenGLRenderer::DrawIndexed(math::mat4 viewProjectionMatrix, uint32_t count) {
		for (uint32_t i = 0; i < m_renderData.TextureSlotIndex; i++) {
			m_material->Set(m_renderData.TextureSlots[i], i);
		}

		m_material->Set("u_ViewProjection", viewProjectionMatrix);
		m_material->Bind();

		m_vertexArray->Bind();

		glDrawElements(
			GL_TRIANGLES,
			count,
			GL_UNSIGNED_INT,
			nullptr
		);
	}

	void OpenGLRenderer::Draw(Texture* texture, const math::mat4& transform, const math::vec2& texCoordMin, const math::vec2& texCoordMax, Color color, float shaderType /*= 1.0f*/) {
		g2dassert(m_isBatcherInitialized, "trying to draw without initializing the sprite batcher?!");

		if (
			m_renderData.quadIndexCount >= m_renderData.MaxIndices ||
			m_renderData.TextureSlotIndex >= m_renderData.MaxTextureSlots
			) {
			NextBatch();
		}

		float textureSlot = -1.0f;

		// searching for the texture on the array
		for (size_t i = 0; i < m_renderData.TextureSlotIndex; i++) {
			if (m_renderData.TextureSlots[i] == texture) {
				textureSlot = (float)i;
				break;
			}
		}

		// if we didn't find it, we add it.
		if (textureSlot == -1.0f) {
			// #todo: check if we are not over the maximum texture slots, if we are we have to flush
			textureSlot = (float)m_renderData.TextureSlotIndex;
			m_renderData.TextureSlots[m_renderData.TextureSlotIndex] = texture;
			m_renderData.TextureSlotIndex++;
		}

		size_t quadVertexCount = 4;

		math::vec2 textureCoords[] = {
			{ texCoordMin.x, texCoordMin.y },
			{ texCoordMax.x, texCoordMin.y },
			{ texCoordMax.x, texCoordMax.y },
			{ texCoordMin.x, texCoordMax.y }
		};

		for (size_t i = 0; i < quadVertexCount; i++) {
			m_renderData.quadVertexPtrPosition->Position = transform * m_renderData.quadVertexPosition[i];
			m_renderData.quadVertexPtrPosition->TexCoord = textureCoords[i];
			m_renderData.quadVertexPtrPosition->TextureSlot = textureSlot;
			m_renderData.quadVertexPtrPosition->color = color;
			m_renderData.quadVertexPtrPosition->shaderType = shaderType;
			m_renderData.quadVertexPtrPosition++;
		}

		m_renderData.quadIndexCount += 6;
	}

	void OpenGLRenderer::StartBatch() {
		m_renderData.TextureSlotIndex = 0;
		m_renderData.quadIndexCount = 0;
		m_renderData.quadVertexPtrPosition = m_renderData.quadVertexBase;
	}

	void OpenGLRenderer::NextBatch() {
		Flush();
		StartBatch();
	}

	void OpenGLRenderer::Flush() {
		uint32_t dataSize = (uint32_t)((uint8_t*)m_renderData.quadVertexPtrPosition - (uint8_t*)m_renderData.quadVertexBase);
		SetBufferData(m_renderData.quadVertexBase, dataSize);
		DrawIndexed(m_renderData.ViewProjection, m_renderData.quadIndexCount);
		m_renderData.RenderStats.DrawCalls++;
	}

}