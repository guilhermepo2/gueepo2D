#pragma once
#include "core/renderer/Renderer.h"
#include "core/math/vec3.h"
#include "core/math/mat4.h"

namespace gueepo {

	class OpenGLShader;
	class OpenGLVertexArray;
	class OpenGLVertexBuffer;

	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer() {}


	protected:
		void SetClearColor(const math::vec3& color) override;
		void SetClearColor(float r, float g, float b, float a) override;
		void Clear() override;
		
		void Initialize_Internal() override;
		void DrawIndexed_Internal(math::mat4 viewProjectionMatrix) override;
		void DrawIndexed_Internal(math::mat4 viewProjectionMatrix, uint32_t count) override;
		std::string GraphicsContextString_Internal() override;
		void SetUnpackAlignment_Internal(int value) override;
		virtual void SetBufferData_Internal(const void* data, uint32_t size) override;

	private:
		OpenGLShader* m_shader;
		OpenGLVertexArray* m_vertexArray;
		OpenGLVertexBuffer* m_vertexBuffer;
	};
}