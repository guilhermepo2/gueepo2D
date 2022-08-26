#include "gueepo2Dpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <SDL.h>
namespace gueepo {

	OpenGLContext::OpenGLContext(SDL_Window* _WindowRef) {
		m_WindowRef = _WindowRef;

		g2dassert(m_WindowRef != nullptr, "Window is null!");
		g2dassert(SDL_WasInit(SDL_INIT_VIDEO), "sdl is not initialized?!");
	}

	void OpenGLContext::Init() {
		m_GLContext = SDL_GL_CreateContext(m_WindowRef);

		SDL_GL_MakeCurrent(m_WindowRef, m_GLContext);
		
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			LOG_ERROR("unable to initialize glad! {0}", glGetError());
		}

		glGetError();

		LOG_INFO("OpenGL version: {0}", glGetString(GL_VERSION));
		LOG_INFO("OpenGL vendor: {0}", glGetString(GL_VENDOR));
		LOG_INFO("OpenGL renderer: {0}", glGetString(GL_RENDERER));
	}

	void OpenGLContext::Swap() {
		// todo: this... should be on the window? why is this on the graphics context?
		SDL_GL_SwapWindow(m_WindowRef);
	}

	std::string OpenGLContext::GraphicsContextString() {
		std::string version = std::string((const char*)glGetString(GL_VERSION));
		std::string versionNumbersOnly = version.substr(0, version.find(' '));

		return "OpenGL " + std::string((const char*)glGetString(GL_VENDOR)) + " " + versionNumbersOnly;
	}

}