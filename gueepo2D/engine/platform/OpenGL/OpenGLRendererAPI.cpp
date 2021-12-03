#include "gueepo2Dpch.h"
#include "OpenGLRendererAPI.h"
#include <glad/glad.h>
#include "core/renderer/VertexArray.h"

namespace gueepo {

	void OpenGLRendererAPI::SetClearColor(const math::Vector3& color) {
		glClearColor(color.x, color.y, color.z, 1.0);
	}

	void OpenGLRendererAPI::SetClearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	}

	void OpenGLRendererAPI::DrawIndexed(VertexArray* vertexArray) {
		glDrawElements(
			GL_TRIANGLES, 
			vertexArray->GetIndexBuffer()->GetCount(), 
			GL_UNSIGNED_INT, 
			nullptr
		);
	}

}