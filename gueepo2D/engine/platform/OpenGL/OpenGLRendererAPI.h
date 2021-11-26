#pragma once
#include "core/renderer/RendererAPI.h"

namespace gueepo {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI() {}

		void SetClearColor(const math::Vector3& color) override;
		void Clear() override;
		void DrawIndexed(VertexArray* vertexArray) override;
	};
}