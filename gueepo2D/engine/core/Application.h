
// ----------------------------------------------------------
// gueepo2D: Application.h
// Defines an application that can use the engine resources
// ----------------------------------------------------------

#pragma once

#include "Window.h"

namespace gueepo {
	
	class WindowCloseEvent;
	class WindowResizeEvent;
	class Layer;

	struct InputState;

	class Application {
	public:
		Application(const std::string& _Title, unsigned int _Width, unsigned int _Height);
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	protected:
		// These should be overriden by the Application!
		virtual void Application_OnInitialize() {}
		virtual void Application_OnDeinitialize() {}
		virtual void Application_OnUpdate(float DeltaTime) { unreferenced(DeltaTime); }
		virtual void Application_OnInput(const InputState& currentInputState) { unreferenced(currentInputState); }
		virtual void Application_OnRender() {}
		virtual void Application_OnEvent(Event& e) { unreferenced(e); }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_bIsRunning;

	private:
		static Application* s_Instance;
	};

	// This is to be defined on the client
	Application* CreateApplication();
}
