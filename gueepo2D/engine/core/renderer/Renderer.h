#pragma once
#include "RendererAPI.h"

namespace gueepo {

	class OrtographicCamera;
	class SpriteBatcher;

	class Renderer {
	public:

		static void Initialize();
		static void Shutdown();

		// static void Submit(VertexArray* vertexArray, Shader* shader);
		static void Begin(const OrtographicCamera& camera);
		static void End();

		static void SetUnpackAlignment(int value);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static SpriteBatcher* s_spriteBatcher;
		static SpriteBatcher* s_uiBatcher;
	};
}