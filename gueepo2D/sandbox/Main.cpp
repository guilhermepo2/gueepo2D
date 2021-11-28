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
			layout (location = 1) in vec2 aTexCoord;
			out vec3 v_Position;
			out vec2 v_TexCoord;

			void main()
			{
				gl_Position = vec4(aPos, 1.0);
				v_TexCoord = aTexCoord;
			}
		)";
const char* sq_fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 v_TexCoord;\n"
"uniform sampler2D textureSampler;"
"void main()\n"
"{\n"
"   FragColor = texture(textureSampler, v_TexCoord);\n"
"}\n\0";

gueepo::Shader* triangleShader = nullptr;
gueepo::Shader* squareShader = nullptr;
gueepo::VertexArray* triangleVA = nullptr;
gueepo::VertexArray* squareVA = nullptr;
gueepo::Texture* duckTexture = nullptr;

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
		duckTexture = gueepo::Texture::Create("./assets/duck_brown.png");

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f
		};

		float squareVertices[5 * 4] = {
			 -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
			 -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
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
				{ gueepo::ShaderDataType::Float2, "a_TexCoord"}
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
		duckTexture->Bind();
		squareShader->Bind();
		gueepo::Renderer::Submit(squareVA);
		// triangleShader->Bind();
		// gueepo::Renderer::Submit(triangleVA);
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
	}

	~DummyApp() { LOG_INFO("deleting dummy app"); }
};

// ================================================================================
// entry point
// ================================================================================
gueepo::Application* gueepo::CreateApplication() {
	return new DummyApp("dummy app!", 1024, 768);
}