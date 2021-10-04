#pragma once
#include "Window.h"

namespace gueepo {
	class Application {
	public:
		Application(const std::string& _Title, unsigned int _Width, unsigned int _Height);
		virtual ~Application();
		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_bIsRunning;
	};

	// This is to be defined on the client
	Application* CreateApplication();
}
