#pragma once
#include "core/renderer/Renderer.h"
#include "core/math/vec3.h"

namespace gueepo {
	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer() {}


	protected:
		void SetClearColor(const math::vec3& color) override;
		void SetClearColor(float r, float g, float b, float a) override;
		void Clear() override;
		
		void Initialize_Internal() override;
		void DrawIndexed_Internal(VertexArray* vertexArray) override;
		void DrawIndexed_Internal(VertexArray* vertexArray, uint32_t count) override;
		std::string GraphicsContextString_Internal() override;
		void SetUnpackAlignment_Internal(int value) override;
	};
}