#include "gueepo2Dpch.h"
#include "SDL2Window.h"
#include <SDL.h>

#include "core/events/ApplicationEvent.h"
#include "core/events/KeyEvent.h"
#include "core/events/MouseEvent.h"
#include "core/renderer/RendererAPI.h"
#include "platform/OpenGL/OpenGLContext.h"

// #todo maybe move this to a "OpenGLIncludes.h" ?
static const int OPENGL_MAJOR_VERSION = 4;
static const int OPENGL_MINOR_VERSION = 5;

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

	void SDL2Window::SetVSync(bool _enabled) {
		m_bIsVSyncEnabled = _enabled;
		// #todo: actually do something here to enable/disable vsync
	}

	void SDL2Window::Initialize(const WindowConfiguration& _config) {
		m_Width = _config.Width;
		m_Height = _config.Height;
		m_Title = _config.Title;

		unsigned int IsSDLInitialized = SDL_WasInit(SDL_INIT_VIDEO);

		if (IsSDLInitialized == 0) {
			SDL_Init(SDL_INIT_VIDEO);
			// #todo: maybe this should be on some sort of renderer backend?
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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

		// #todo have a parameter informing if should be resizable or not?!
		m_Window = SDL_CreateWindow(
			m_Title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_Width,
			m_Height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		);

		assert(m_Window, "unable to create window: {0}", SDL_GetError());

		// #todo: set this somewhere else?
		RendererAPI::SetAPI(RendererAPI::API::OpenGL);
		m_GraphicsContext = GraphicsContext::Create(m_Window);
		m_GraphicsContext->Init();

		SetVSync(true);


		LOG_INFO("window was created successfully! ({0}, {1}, {2})", m_Title, m_Width, m_Height);
	}

	void SDL2Window::Shutdown() {
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}

}