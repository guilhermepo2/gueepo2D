#include "gueepo2Dpch.h"
#include "Application.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/EventDispatcher.h"
#include "core/ImGuiLayer.h"
#include "core/input/Input.h"
#include "core/TimeStep.h"

// #all temp
#include <SDL.h>
#include <glad/glad.h>
#include "core/renderer/Shader.h"
#include "core/renderer/IndexBuffer.h"
#include "core/renderer/VertexBuffer.h"
#include "core/renderer/BufferLayout.h"
#include "core/renderer/VertexArray.h"

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

		const char* vertexShaderSource = R"(
			# version 330 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				gl_Position = vec4(aPos, 1.0);
				v_Position = aPos;
				v_Color = a_Color;
			}
		)";
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec3 v_Position;\n"
			"in vec4 v_Color;\n"
			"void main()\n"
			"{\n"
			"   FragColor = v_Color;\n"
			"}\n\0";

		const char* sq_vertexShaderSource = R"(
			# version 330 core
			layout (location = 0) in vec3 aPos;
			out vec3 v_Position;

			void main()
			{
				gl_Position = vec4(aPos, 1.0);
			}
		)";
		const char* sq_fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(0.2, 0.3, 0.8, 1.0);\n"
			"}\n\0";

		Shader* ourShader = Shader::Create(vertexShaderSource, fragmentShaderSource);
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, // left  
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, // right 
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f // top   
		};

		VertexArray* ourVertexArray = VertexArray::Create();
		VertexBuffer* ourVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position"},
				{ ShaderDataType::Float4, "a_Color"},
			};
			ourVertexBuffer->SetLayout(layout);
		}
		ourVertexArray->AddVertexBuffer(ourVertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		IndexBuffer* ourIndexBuffer = IndexBuffer::Create(indices, 3);
		ourVertexArray->SetIndexBuffer(ourIndexBuffer);
		ourVertexArray->Unbind(); 

		Shader* sq_Shader = Shader::Create(sq_vertexShaderSource, sq_fragmentShaderSource);
		VertexArray* squareVA = VertexArray::Create();
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			 -0.75f,  0.75f, 0.0f 
		};

		VertexBuffer* squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position"},
			};
			squareVB->SetLayout(layout);
		}
		squareVA->AddVertexBuffer(squareVB);

		unsigned int sq_indices[6] = { 0, 1, 2, 2, 3, 0 };
		IndexBuffer* sq_IndexBuffer = IndexBuffer::Create(sq_indices, 6);
		squareVA->SetIndexBuffer(sq_IndexBuffer);
		squareVA->Unbind();

		LOG_INFO("application is running!");
		while (m_bIsRunning) {
			float DeltaTime = static_cast<float>((timestep::GetTicks() - TicksLastFrame)) / 1000.0f;
			TicksLastFrame = timestep::GetTicks();
			// process input before update
			inputSystem->PrepareForUpdate();
			inputSystem->Update();

			for (Layer* l : m_LayerStack) {
				l->OnInput(inputSystem->GetState());
			}

			for (Layer* l : m_LayerStack) {
				l->OnUpdate(DeltaTime);
			}

			glClearColor(0.1, 0.1, 0.1, 0.1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_ImGuiLayer->Begin();
			for (Layer* l : m_LayerStack) {
				l->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			sq_Shader->Bind();
			squareVA->Bind();
			glDrawElements(GL_TRIANGLES, squareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			ourShader->Bind();
			ourVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, ourVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			

			m_Window->Update();
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
