#pragma once
#include "core/renderer/RendererAPI.h"

namespace gueepo {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI() {}

		void SetClearColor(const math::vec3& color) override;
		void SetClearColor(float r, float g, float b, float a) override;
		void Clear() override;
		void DrawIndexed(VertexArray* vertexArray) override;
		void DrawIndexed(VertexArray* vertexArray, uint32_t count) override;
		void SetUnpackAlignment(int value) override;
	};
}