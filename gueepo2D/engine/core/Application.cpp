#include "Application.h"

#include "core/Log.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/EventDispatcher.h"
#include "core/input/Input.h"
#include "core/TimeStep.h"
#include "core/renderer/Renderer.h"
#include "core/audio/Audio.h"
#include "core/input/Input.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

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

#if GUEEPO2D_DEBUG
        LOG_INFO("DEBUG BUILD");
		m_Window->AddPlatformToTitle();
#endif

#if GUEEPO2D_RELEASE
        LOG_INFO("RELEASE BUILD");
#endif
	}

	Application::~Application() {
		Application_OnDeinitialize();
	}

#if __EMSCRIPTEN__
    static int TicksLastFrame = 0;
    static InputSystem* inputSystem = nullptr;
    void EmscriptenMainLoop(void* App) {
        // LOG_INFO("EMSCRIPTEN MAIN LOOP...");
        Application* application = static_cast<gueepo::Application*>(App);

        float DeltaTime = static_cast<float>((timestep::GetTicks() - TicksLastFrame)) / 1000.0f;
        TicksLastFrame = timestep::GetTicks();
        // LOG_INFO("DeltaTime: {0}", DeltaTime);
        inputSystem->PrepareForUpdate();
        application->m_Window->Update();
        inputSystem->Update();

        application->Application_OnInput(inputSystem->GetState());
        application->Application_OnUpdate(DeltaTime);
        application->Application_OnRender();

        application->m_Window->Swap();

        // delaying until next frame so we can keep 60fps
        int TimeToWait = FRAME_TARGET_TIME - (timestep::GetTicks() - TicksLastFrame);
        if (TimeToWait > 0.0f && TimeToWait <= FRAME_TARGET_TIME) {
            timestep::Sleep(TimeToWait);
        }
    }
#endif

	void Application::Run() {
		Application_OnInitialize();

		LOG_INFO("application is running!");
        LOG_INFO("Starting application loop.");
#ifdef __EMSCRIPTEN__
        LOG_INFO("EMSCRIPTEN MAIN LOOP");
        InputSystem::s_Instance->Initialize();
        inputSystem = InputSystem::s_Instance;
        emscripten_set_main_loop_arg(&EmscriptenMainLoop, this, 0, 1);
        LOG_INFO("CALLED THE LOOP!");
#else
        InputSystem* inputSystem = InputSystem::s_Instance;
        inputSystem->Initialize();
        m_bIsRunning = true;
        int TicksLastFrame = 0;
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
#endif

        LOG_INFO("Finished application loop!");
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
