#include "SDL2Window.h"
#include <SDL.h>

#include "core/Log.h"
#include "core/Common.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/KeyEvent.h"
#include "core/events/MouseEvent.h"
#include "core/renderer/Renderer.h"

// #todo maybe move this to a "OpenGLIncludes.h" ?
#if GUEEPO2D_MACOS
static const int OPENGL_MAJOR_VERSION = 3;
static const int OPENGL_MINOR_VERSION = 3;
#elif __EMSCRIPTEN__
static const int OPENGL_MAJOR_VERSION = 3;
static const int OPENGL_MINOR_VERSION = 0;
#else
static const int OPENGL_MAJOR_VERSION = 3;
static const int OPENGL_MINOR_VERSION = 3;
#endif

namespace gueepo {

	Window* Window::CreateNewWindow(const WindowConfiguration& _config) {
		return new SDL2Window(_config);
	}

	SDL2Window::SDL2Window(const WindowConfiguration& _config) {
		Initialize(_config);
	}

	SDL2Window::~SDL2Window() {
		Shutdown();
	}

	void SDL2Window::Update() {
		SDL_Event SDLEvent;
		while (SDL_PollEvent(&SDLEvent)) {

			switch (SDLEvent.type) {
			case SDL_WINDOWEVENT: {
				switch (SDLEvent.window.event) {
				case SDL_WINDOWEVENT_SHOWN:
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_FOCUS_GAINED:
				case SDL_WINDOWEVENT_ENTER:
				case SDL_WINDOWEVENT_FOCUS_LOST:
				case SDL_WINDOWEVENT_LEAVE:
				case SDL_WINDOWEVENT_MOVED: {
					// #todo: event not implemented yet!
				} break;
				case SDL_WINDOWEVENT_RESIZED: {
					WindowResizeEvent event(SDLEvent.window.data1, SDLEvent.window.data2);
					m_EventCallback(event);
				} break;
				}
			} break;
			case SDL_QUIT: {
				WindowCloseEvent event;
				m_EventCallback(event);
			} break;
			case SDL_KEYDOWN: {
				KeyPressedEvent event(SDLEvent.key.keysym.sym, SDLEvent.key.repeat);
				m_EventCallback(event);
			} break;
			case SDL_KEYUP: {
				KeyReleasedEvent event(SDLEvent.key.keysym.sym);
				m_EventCallback(event);
			} break;
			case SDL_MOUSEMOTION: {
				MouseMovedEvent event(
					static_cast<float>(SDLEvent.motion.x), 
					static_cast<float>(SDLEvent.motion.y)
				);
				m_EventCallback(event);
			} break;
			case SDL_MOUSEBUTTONDOWN: {
				MouseButtonPressedEvent event(SDLEvent.button.button);
				m_EventCallback(event);
			} break;
			case SDL_MOUSEBUTTONUP: {
				MouseButtonReleasedEvent event(SDLEvent.button.button);
				m_EventCallback(event);
			} break;
			case SDL_MOUSEWHEEL: {
				MouseScrolledEvent event(
					static_cast<float>(SDLEvent.wheel.x), 
					static_cast<float>(SDLEvent.wheel.y)
				);
				m_EventCallback(event);
			} break;
			}
		}
	}

	void SDL2Window::Swap() {
		SDL_GL_SwapWindow(m_Window);
	}

	void SDL2Window::SetVSync(bool _enabled) {
		m_bIsVSyncEnabled = _enabled;
		// #todo: actually do something here to enable/disable vsync
	}

	void SDL2Window::AddPlatformToTitle() {
		SDL_SetWindowTitle(m_Window, std::string(m_Title + " <" + Renderer::GraphicsContextString() + ">").c_str());
	}

	void SDL2Window::Initialize(const WindowConfiguration& _config) {
		m_Width = _config.Width;
		m_Height = _config.Height;
		m_Title = _config.Title;

		unsigned int IsSDLInitialized = SDL_WasInit(SDL_INIT_VIDEO);

		if (IsSDLInitialized == 0) {
			SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
#ifdef __EMSCRIPTEN__
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#else
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		}

		LOG_INFO("sdl initialized, platform detected: {0}", SDL_GetPlatform());
		int numVideoDrivers = SDL_GetNumVideoDrivers();
		LOG_INFO("sdl initialized, number of devices available: {0}", numVideoDrivers);
		for (int i = 0; i < numVideoDrivers; i++) {
			LOG_INFO("\tdevice available: {0}", SDL_GetVideoDriver(i));
		}

		// #todo have a parameter informing if should be resizable or not?!
		m_Window = SDL_CreateWindow(
			m_Title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_Width,
			m_Height,
			SDL_WINDOW_OPENGL // | SDL_WINDOW_RESIZABLE - it's a videogame! no resizing the window!
		);

		LOG_INFO("SDL2 window created");
		g2dassert(m_Window, "unable to create window: {0}", SDL_GetError());

		m_OpenGLContext = SDL_GL_CreateContext(m_Window);
		SDL_GL_MakeCurrent(m_Window, m_OpenGLContext);
		SetVSync(true);

		LOG_INFO("window was created successfully! ({0}, {1}, {2})", m_Title, m_Width, m_Height);
	}

	void SDL2Window::Shutdown() {
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}

}