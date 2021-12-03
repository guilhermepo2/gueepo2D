#pragma once
#include "core/math/Vector3.h"

namespace gueepo {

	class VertexArray;

	class RendererAPI {
	public:

		enum class API {
			None = 0,
			OpenGL = 1,
			Vulkan = 2,
			DirectX = 3,
			Metal = 4
		};

	public:
		virtual void SetClearColor(const math::Vector3& color) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(VertexArray* vertexArray) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}