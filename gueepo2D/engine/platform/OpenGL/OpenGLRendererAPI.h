#pragma once
#include "core/renderer/RendererAPI.h"

namespace gueepo {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI() {}

		void SetClearColor(const math::Vector3& color) override;
		void SetClearColor(float r, float g, float b, float a) override;
		void Clear() override;
		void DrawIndexed(VertexArray* vertexArray) override;
	};
}