#include "gueepo2Dpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <SDL.h>
namespace gueepo {

	OpenGLContext::OpenGLContext(SDL_Window* _WindowRef) {
		m_WindowRef = _WindowRef;

		assert(m_WindowRef != nullptr, "Window is null!");
		assert(SDL_WasInit(SDL_INIT_VIDEO), "sdl is not initialized?!");
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
		SDL_GL_SwapWindow(m_WindowRef);
	}

}