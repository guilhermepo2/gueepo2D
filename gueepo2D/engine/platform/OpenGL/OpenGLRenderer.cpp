#include "gueepo2Dpch.h"
#include "OpenGLRenderer.h"
#include <SDL.h>
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

	void OpenGLRenderer::Initialize_Internal() {
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			LOG_ERROR("unable to initialize glad! {0}", glGetError());
		}

		glGetError();

		LOG_INFO("OpenGL version: {0}", glGetString(GL_VERSION));
		LOG_INFO("OpenGL vendor: {0}", glGetString(GL_VENDOR));
		LOG_INFO("OpenGL renderer: {0}", glGetString(GL_RENDERER));
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

	std::string OpenGLRenderer::GraphicsContextString_Internal() {
		std::string version = std::string((const char*)glGetString(GL_VERSION));
		std::string versionNumbersOnly = version.substr(0, version.find(' '));

		return "OpenGL " + std::string((const char*)glGetString(GL_VENDOR)) + " " + versionNumbersOnly;
	}

	void OpenGLRenderer::SetUnpackAlignment_Internal(int value) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, value);
	}

}