#pragma once
#include "core/math/mat4.h"
#include "core/math/vec2.h"
#include "core/renderer/Color.h"

namespace gueepo {

	class FontSprite;
	class OrtographicCamera;
	class Texture;
	class RendererAPI;
	class Shader;
	class string;

	class VertexBuffer;
	class VertexArray;

	struct QuadVertex {
		gueepo::math::vec3 Position;
		gueepo::math::vec2 TexCoord;
		float TextureSlot = 0.0f;
		gueepo::Color color;
	};

	struct RenderData {
		math::mat4 ViewProjection;

		// Maximum
		static const uint32_t MaxQuads = 1000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 16;

		// Defaults
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
	};

	class SpriteBatcher {
	public:
		void Initialize(RendererAPI* rendererAPI, Shader* batchShader);
		void Shutdown();

		void Begin(const OrtographicCamera& camera);
		void End();
		void Flush();

		void Draw(const math::mat4& transform, const math::vec2& textureCoordMin, const math::vec2& textureCoordMax, Texture* texture, Color color);
		void Draw(const math::mat4& transform, const math::vec2& textureCoordMin, const math::vec2& textureCoordMax, Texture* texture);
		void Draw(const math::mat4& transform, Texture* texture);
		void Draw(const math::vec2& position, Texture* texture);
		void Draw(Texture* texture); // hey... I don't know why you would ask us to just draw a texture, but hey, you have the option!
		void DrawText(FontSprite* fontSprite, gueepo::string text, const math::vec2& position, float scale, Color color);

		int GetDrawCalls();

	private:
		void StartBatch();
		void NextBatch();

		RendererAPI* m_RendererAPI;
		Shader* m_batchShader;
		RenderData m_renderData;
	};
}