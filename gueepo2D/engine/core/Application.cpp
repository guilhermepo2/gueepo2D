#include "gueepo2Dpch.h"
#include "Application.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/EventDispatcher.h"

// #todo: temp
#include "SDL.h"
const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

namespace gueepo {

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application(const std::string& _Title, unsigned int _Width, unsigned int _Height) {

		WindowConfiguration c = { _Title, _Width, _Height };
		m_Window = std::unique_ptr<Window>(Window::CreateNewWindow(c));
		m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));
	}

	Application::~Application() {}

	void Application::Run() {
		m_bIsRunning = true;
		float TicksLastFrame = 0.0f;

		LOG_INFO("application is running!");
		// #todo: call Application::Start here?
		while (m_bIsRunning) {

			// #todo: this has to be in its own platform independent class
			float DeltaTime = static_cast<float>((SDL_GetTicks() - TicksLastFrame)) / 1000.0f;
			DeltaTime = (DeltaTime > 0.05f) ? 0.05f : DeltaTime;
			TicksLastFrame = SDL_GetTicks();
			// ----------------------------------------------------------

			for (Layer* l : m_LayerStack) {
				l->OnUpdate(DeltaTime);
			}
			m_Window->Update();

			// ----------------------------------------------------------
			// delaying until next frame so we can keep 60fps
			int TimeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - TicksLastFrame);
			if (TimeToWait > 0.0f && TimeToWait <= FRAME_TARGET_TIME) {
				SDL_Delay(TimeToWait);
			}
			// ----------------------------------------------------------
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			if (e.Handled()) {
				break;
			}

			(*it)->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer* l) {
		m_LayerStack.PushLayer(l);
	}

	void Application::PushOverlay(Layer* l) {
		m_LayerStack.PushOverlay(l);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		unreferenced(e);
		m_bIsRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		LOG_INFO(e);
		return true;
	}

}
