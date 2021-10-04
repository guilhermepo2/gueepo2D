#include "gueepo2Dpch.h"
#include "Application.h"
#include "Log.h"

namespace gueepo {

	Application::Application(const std::string& _Title, unsigned int _Width, unsigned int _Height) {

		WindowConfiguration c = { _Title, _Width, _Height };
		m_Window = std::unique_ptr<Window>(Window::CreateNewWindow(c));
	
	}

	Application::~Application()
	{

	}

	void Application::Run() {
		m_bIsRunning = true;

		LOG_INFO("application is running!");
		while (m_bIsRunning) {
			m_Window->Update();
			// calculate delta time
			// handle events
			// handle input
			// handle update
			// handle render
		}
	}

}
