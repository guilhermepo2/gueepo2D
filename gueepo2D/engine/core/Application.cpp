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

// For now locking this to run at 60fps
const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

namespace gueepo {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		case ShaderDataType::None:
		default:
			break;

		}
	}

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

		Shader* ourShader = Shader::Create(vertexShaderSource, fragmentShaderSource);
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, // left  
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, // right 
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f // top   
		};

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		VertexBuffer* ourVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position"},
				{ ShaderDataType::Float4, "a_Color"},
			};
			ourVertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		for (const auto& element : ourVertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				element.GetCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, 
				ourVertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset
			);
			index++;
		}
		
		unsigned int indices[3] = { 0, 1, 2 };
		IndexBuffer* ourIndexBuffer = IndexBuffer::Create(indices, 3);

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

			ourShader->Bind();
			glBindVertexArray(VAO);
			// glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, ourIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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
