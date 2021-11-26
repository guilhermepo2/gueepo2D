#include "gueepo2Dpch.h"
#include "OpenGLRendererAPI.h"
#include <glad/glad.h>
#include "core/renderer/VertexArray.h"

namespace gueepo {

	void OpenGLRendererAPI::SetClearColor(const math::Vector3& color) {
		glClearColor(color.x, color.y, color.z, 1.0);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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