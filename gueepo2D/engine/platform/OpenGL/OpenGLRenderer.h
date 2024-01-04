#pragma once
#include "core/renderer/Color.h"
#include "core/renderer/Renderer.h"
#include "core/math/vec3.h"
#include "core/math/mat4.h"
#include <array>

namespace gueepo {

	class OpenGLMaterial;
	class OpenGLShader;
	class OpenGLVertexArray;
	class OpenGLVertexBuffer;

	struct QuadVertex {
		math::vec3 Position;
		math::vec2 TexCoord;
		float TextureSlot = 0.0f;
		Color color;
		float shaderType = 0.0;
	};

	struct RenderData {
		gueepo::math::mat4 ViewProjection;

		// Max
		static const uint32_t MaxQuads = 2500;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 16;

		// Defaults
		math::vec3 quadVertexPosition[4];

		uint32_t TextureSlotIndex = 0;

		// Quad Vertex Counting
		uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBase = nullptr;
		QuadVertex* quadVertexPtrPosition = nullptr;

		struct {
			uint32_t DrawCalls;
		} RenderStats = { 0 };

	};

	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer() {}
	protected:
		void SetClearColor(const math::vec3& color) override;
		void SetClearColor(float r, float g, float b, float a) override;
		void Clear() override;
		
		void Initialize_Internal() override;
		void Shutdown_Internal() override;
		std::string GraphicsContextString_Internal() override;
		void SetUnpackAlignment_Internal(int value) override;

		// Effectively Drawing
		void BeginFrame_Internal(const OrtographicCamera& camera) override;
		void Draw_Internal(Texture* texture, const math::mat4& transform, const math::vec2& texCoordMin, const math::vec2& texCoordMax, Color color) override;
		void DrawString_Internal(FontSprite* fontSprite, gueepo::string text, const math::vec2& position, float scale, Color color) override;
		void EndFrame_Internal() override;

	private:
		OpenGLMaterial* m_material = nullptr;
		OpenGLShader* m_shader = nullptr;
		OpenGLVertexArray* m_vertexArray = nullptr;
		OpenGLVertexBuffer* m_vertexBuffer = nullptr;

		// Private OpenGL Specifics
		void SetBufferData(const void* data, uint32_t size);
		void DrawIndexed(math::mat4 viewProjectionMatrix);
		void DrawIndexed(math::mat4 viewProjectionMatrix, uint32_t count);

		void Draw(Texture* texture, const math::mat4& transform, const math::vec2& texCoordMin, const math::vec2& texCoordMax, Color color, float shaderType = 1.0f);

		// Batching
		RenderData m_renderData;
		bool m_isBatcherInitialized = false;
		void StartBatch();
		void NextBatch();
		void Flush();
	};
}