#pragma once

namespace gueepo {
	class RendererAPI {
	public:

		enum class API {
			None = 0,
			OpenGL = 1,
			Vulkan = 2,
			DirectX = 3,
			Metal = 4
		};

		static API GetAPI() { return s_API; }
		static void SetAPI(API _API) { s_API = _API; }
	private:
		static API s_API;
	};
}