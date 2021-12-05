#include "gueepo2Dpch.h"
#include "Application.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/EventDispatcher.h"
#include "core/ImGuiLayer.h"
#include "core/input/Input.h"
#include "core/TimeStep.h"
#include "core/renderer/Renderer.h"


// For now locking this to run at 60fps
const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

namespace gueepo {

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& _Title, unsigned int _Width, unsigned int _Height) {

		assert(s_Instance == nullptr, "application already exists!");
		s_Instance = this;

		WindowConfiguration c = { _Title, _Width, _Height };
		m_Window = std::unique_ptr<Window>(Window::CreateNewWindow(c));
		m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {}

	void Application::Run() {

		m_bIsRunning = true;
		int TicksLastFrame = 0;
		
		InputSystem* inputSystem = InputSystem::s_Instance;
		inputSystem->Initialize();

		LOG_INFO("application is running!");
		while (m_bIsRunning) {
			float DeltaTime = static_cast<float>((timestep::GetTicks() - TicksLastFrame)) / 1000.0f;
			TicksLastFrame = timestep::GetTicks();
			// process input before update
			inputSystem->PrepareForUpdate();
			m_Window->Update();
			inputSystem->Update();

			for (Layer* l : m_LayerStack) {
				l->OnInput(inputSystem->GetState());
			}

			for (Layer* l : m_LayerStack) {
				l->OnUpdate(DeltaTime);
			}

			// #todo: have a way to set the color to be cleared (maybe put it on the camera)
			// RenderCommand::SetClearColor(gueepo::math::Vector3(0.1f, 0.1f, 0.1f));
			// RenderCommand::Clear();
			for (Layer* l : m_LayerStack) {
				// Renderer::BeginScene(cam);
				l->OnRender();
				// Renderer::EndScene();
			}

			m_ImGuiLayer->Begin();
			for (Layer* l : m_LayerStack) {
				l->OnImGuiRender();
			}
			m_ImGuiLayer->End();

	
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

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			if (e.Handled()) {
				break;
			}

			(*it)->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer* l) {
		m_LayerStack.PushLayer(l);
		l->OnAttach();
	}

	void Application::PushOverlay(Layer* l) {
		m_LayerStack.PushOverlay(l);
		l->OnAttach();
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
