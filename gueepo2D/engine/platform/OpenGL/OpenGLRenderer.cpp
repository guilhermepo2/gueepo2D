#include "gueepo2Dpch.h"
#include "OpenGLRenderer.h"
#include <glad/glad.h>
#include "core/renderer/VertexArray.h"

namespace gueepo {

	void OpenGLRenderer::SetClearColor(const math::vec3& color) {
		glClearColor(color.x, color.y, color.z, 1.0);
	}

	void OpenGLRenderer::SetClearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void OpenGLRenderer::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderer::DrawIndexed_Internal(VertexArray* vertexArray) {
		glDrawElements(
			GL_TRIANGLES, 
			vertexArray->GetIndexBuffer()->GetCount(), 
			GL_UNSIGNED_INT, 
			nullptr
		);
	}

	void OpenGLRenderer::DrawIndexed_Internal(VertexArray* vertexArray, uint32_t count) {
		glDrawElements(
			GL_TRIANGLES,
			count,
			GL_UNSIGNED_INT,
			nullptr
		);
	}

	void OpenGLRenderer::SetUnpackAlignment_Internal(int value) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, value);
	}

}