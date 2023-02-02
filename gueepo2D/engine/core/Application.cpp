#include "Application.h"

#include "core/Log.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/EventDispatcher.h"
#include "core/input/Input.h"
#include "core/TimeStep.h"
#include "core/renderer/Renderer.h"
#include "core/audio/Audio.h"

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

namespace gueepo {

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& _Title, unsigned int _Width, unsigned int _Height) {

		g2dassert(s_Instance == nullptr, "application already exists!");
		s_Instance = this;

		WindowConfiguration c = { _Title, _Width, _Height };
		m_Window = Window::CreateNewWindow(c);
		m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));

		Renderer::Initialize();
		Audio::Init();
		m_Window->AddPlatformToTitle();
	}

	Application::~Application() {
		Application_OnDeinitialize();
	}

	void Application::Run() {

		m_bIsRunning = true;
		int TicksLastFrame = 0;
		
		InputSystem* inputSystem = InputSystem::s_Instance;
		inputSystem->Initialize();

		Application_OnInitialize();
		LOG_INFO("application is running!");
		while (m_bIsRunning) {
			float DeltaTime = static_cast<float>((timestep::GetTicks() - TicksLastFrame)) / 1000.0f;
			TicksLastFrame = timestep::GetTicks();
			inputSystem->PrepareForUpdate();
			m_Window->Update();
			inputSystem->Update();

			Application_OnInput(inputSystem->GetState());
			Application_OnUpdate(DeltaTime);
			Application_OnRender();

			m_Window->Swap();

			// delaying until next frame so we can keep 60fps
			int TimeToWait = FRAME_TARGET_TIME - (timestep::GetTicks() - TicksLastFrame);
			if (TimeToWait > 0.0f && TimeToWait <= FRAME_TARGET_TIME) {
				timestep::Sleep(TimeToWait);
			}
		}

		inputSystem->Shutdown();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(Application::OnWindowResize));

		Application_OnEvent(e);
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
