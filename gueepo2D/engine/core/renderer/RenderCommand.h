#pragma once
#include "RendererAPI.h"

// render command is almost like a static wrap of the renderer API

namespace gueepo {
	class RenderCommand {
	public:

		inline static void SetClearColor(const math::Vector3& color) { s_RendererAPI->SetClearColor(color); }
		inline static void SetClearColor(float r, float g, float b, float a) { s_RendererAPI->SetClearColor(r, g, b, a); }

		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(VertexArray* vertexArray) {
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}