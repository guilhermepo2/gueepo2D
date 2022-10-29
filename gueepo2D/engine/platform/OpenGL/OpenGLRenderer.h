#pragma once
#include "core/renderer/Renderer.h"
#include "core/math/vec3.h"

namespace gueepo {
	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer() {}

		void DrawIndexed(VertexArray* vertexArray) override;
		void DrawIndexed(VertexArray* vertexArray, uint32_t count) override;

	protected:
		void SetClearColor(const math::vec3& color) override;
		void SetClearColor(float r, float g, float b, float a) override;
		void Clear() override;
		
		void SetUnpackAlignment_Internal(int value) override;
	};
}