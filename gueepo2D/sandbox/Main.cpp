#include <gueepo2d.h>
#include <imgui.h>

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

gueepo::Shader* triangleShader = nullptr;
gueepo::Shader* squareShader = nullptr;
gueepo::VertexArray* triangleVA = nullptr;
gueepo::VertexArray* squareVA = nullptr;

// ================================================================================
// Test Functions
void TestLoadSaveImage();

// ================================================================================
// example of user defined layers
// ================================================================================
class ExampleLayer : public gueepo::Layer {
public:
	ExampleLayer() : Layer("MyLayer") {}

	void OnAttach() override {
		triangleShader = gueepo::Shader::Create(vertexShaderSource, fragmentShaderSource);
		squareShader = gueepo::Shader::Create(sq_vertexShaderSource, sq_fragmentShaderSource);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f
		};

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			 -0.75f,  0.75f, 0.0f
		};

		unsigned int indices[3] = { 0, 1, 2 };
		unsigned int sq_indices[6] = { 0, 1, 2, 2, 3, 0 };

		// =================================================================
		// triangle
		// =================================================================
		triangleVA = gueepo::VertexArray::Create();
		gueepo::VertexBuffer* triangleVB = gueepo::VertexBuffer::Create(vertices, sizeof(vertices));
		{
			gueepo::BufferLayout layout = {
				{ gueepo::ShaderDataType::Float3, "a_Position"},
				{ gueepo::ShaderDataType::Float4, "a_Color"},
			};
			triangleVB->SetLayout(layout);
		}
		triangleVA->AddVertexBuffer(triangleVB);

		
		gueepo::IndexBuffer* triangleIB = gueepo::IndexBuffer::Create(indices, 3);
		triangleVA->SetIndexBuffer(triangleIB);
		triangleVA->Unbind();

		// =================================================================
		// square
		// =================================================================
		squareVA = gueepo::VertexArray::Create();

		gueepo::VertexBuffer* squareVB = gueepo::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		{
			gueepo::BufferLayout layout = {
				{ gueepo::ShaderDataType::Float3, "a_Position"},
			};
			squareVB->SetLayout(layout);
		}
		squareVA->AddVertexBuffer(squareVB);

		
		gueepo::IndexBuffer* sq_IndexBuffer = gueepo::IndexBuffer::Create(sq_indices, 6);
		squareVA->SetIndexBuffer(sq_IndexBuffer);
		squareVA->Unbind();
	}

	void OnDetach() override {}

	void OnUpdate(float DeltaTime) override {
		unreferenced(DeltaTime);
	}

	void OnInput(const gueepo::InputState& currentInputState) {
		if (currentInputState.Mouse.WasMouseKeyPressedThisFrame(gueepo::Mousecode::MOUSE_LEFT)) {
			LOG_INFO("Mouse Button Pressed!");
		}
	}

	void OnEvent(gueepo::Event& e) override {
		unreferenced(e);
	}

	virtual void OnRender() {
		squareShader->Bind();
		gueepo::Renderer::Submit(squareVA);
		triangleShader->Bind();
		gueepo::Renderer::Submit(triangleVA);
	}

	void OnImGuiRender() { }
};

// ================================================================================
// application class
// ================================================================================
class DummyApp : public gueepo::Application {
public:
	
	DummyApp(const std::string& _Title, unsigned int _Width, unsigned int _Height) 
		: Application(_Title, _Width, _Height) {
		PushLayer(new ExampleLayer());
		TestLoadSaveImage();
	}

	~DummyApp() { LOG_INFO("deleting dummy app"); }
};

// ================================================================================
// entry point
// ================================================================================
gueepo::Application* gueepo::CreateApplication() {
	return new DummyApp("dummy app!", 1024, 768);
}

// ================================================================================
// ================================================================================
//	TEST FUNCTIONS
// ================================================================================
// ================================================================================

void TestLoadSaveImage() {
	int w;
	int h;
	int comp;
	unsigned char* image = gueepo::g_LoadImage("assets/whataweek.png", w, h, comp);
	gueepo::g_SaveImage("assets/whataweek2.png", w, h, comp, image);
	gueepo::g_FreeImage(image);
}