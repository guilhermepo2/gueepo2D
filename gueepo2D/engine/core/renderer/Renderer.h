#pragma once
#include "RendererAPI.h"

namespace gueepo {

	class OrtographicCamera;
	class Shader;
	class SpriteBatcher;

	class Renderer {
	public:

		static void Initialize();
		static void Shutdown();
		static void Clear(float r, float g, float b, float a);
		static void SetUnpackAlignment(int value);

		// #todo: ehrm........ not sure if I want this
		static RendererAPI* GetRendererAPI();

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}