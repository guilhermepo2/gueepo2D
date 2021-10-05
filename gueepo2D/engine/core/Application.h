#pragma once
#include "Window.h"

namespace gueepo {
	
	class WindowCloseEvent;
	class WindowResizeEvent;

	class Application {
	public:
		Application(const std::string& _Title, unsigned int _Width, unsigned int _Height);
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_bIsRunning;
	};

	// This is to be defined on the client
	Application* CreateApplication();
}
