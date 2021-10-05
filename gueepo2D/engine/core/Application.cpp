#include "gueepo2Dpch.h"
#include "Application.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/EventDispatcher.h"

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

		LOG_INFO("application is running!");
		while (m_bIsRunning) {
			// #todo: calculate delta time
			for (Layer* l : m_LayerStack) {
				l->OnUpdate(.0f);
			}

			m_Window->Update();
			
			// calculate delta time
			// handle events
			// handle input
			// handle update
			// handle render
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
