#pragma once
#include "Window.h"
#include "core/layer/LayerStack.h"

namespace gueepo {
	
	class WindowCloseEvent;
	class WindowResizeEvent;
	class Layer;

	class Application {
	public:
		Application(const std::string& _Title, unsigned int _Width, unsigned int _Height);
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* l);
		void PushOverlay(Layer* l);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_bIsRunning;
		LayerStack m_LayerStack;
	};

	// This is to be defined on the client
	Application* CreateApplication();
}
