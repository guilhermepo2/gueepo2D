#pragma once
#include "core/math/mat4.h"
#include "core/math/vec2.h"
#include "core/renderer/Color.h"
#include <array>

namespace gueepo {

	class FontSprite;
	class OrtographicCamera;
	class Texture;
	class Renderer;
	class Shader;
	class string;

	class VertexBuffer;
	class VertexArray;
	class TextureRegion;

	struct QuadVertex {
		gueepo::math::vec3 Position;
		gueepo::math::vec2 TexCoord;
		float TextureSlot = 0.0f;
		gueepo::Color color;
		float shaderType;
	};

	struct RenderData {
		math::mat4 ViewProjection;

		// Maximum
		static const uint32_t MaxQuads = 1000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 16;

		// Defaults
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
		void Initialize();
		void Shutdown();

		void Begin(const OrtographicCamera& camera);
		void End();
		void Flush();

		// Drawing Textures
		void Draw(Texture* texture, const math::vec2& position, const math::vec2& scale);
		void Draw(Texture* texture, int x, int y, int w, int h, Color color);
		void Draw(Texture* texture, int x, int y, int w, int h);
		void Draw(Texture* texture, int x, int y);
		void Draw(Texture* texture);

		// Drawing Texture Regions
		void Draw(TextureRegion* texRegion, int x, int y, int w, int h, Color color);
		void Draw(TextureRegion* texRegion, int x, int y, int w, int h);
		void Draw(TextureRegion* texRegion, int x, int y);

		// Drawing Text
		void DrawString(FontSprite* fontSprite, gueepo::string text, const math::vec2& position, float scale, Color color);

		int GetDrawCalls();

	private:
		// Hiding these absolute monsters that are drawing textures with transforms and texture coords but that are actually how it's done
		void Draw(Texture* texture, const math::mat4& transform, const math::vec2& textureCoordMin, const math::vec2& textureCoordMax, Color color, float shaderType = 1.0f);
		void Draw(Texture* texture, const math::mat4& transform, const math::vec2& textureCoordMin, const math::vec2& textureCoordMax);

		void StartBatch();
		void NextBatch();

		RenderData m_renderData;
		bool m_isInitialized = false;
	};
}