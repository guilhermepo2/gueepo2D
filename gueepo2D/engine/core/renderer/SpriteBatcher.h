#pragma once
#include "core/math/mat4.h"
#include "core/math/vec2.h"

namespace gueepo {

	class Color;
	class FontSprite;
	class OrtographicCamera;
	class Texture;
	class RendererAPI;
	class Shader;
	class string;

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
	};
}