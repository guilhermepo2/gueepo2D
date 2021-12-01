#include <gueepo2d.h>
#include <imgui.h>

const char* sq_vertexShaderSource = R"(
			# version 330 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec2 aTexCoord;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec2 v_TexCoord;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(aPos, 1.0);
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

gueepo::Shader* squareShader = nullptr;
gueepo::VertexArray* squareVA = nullptr;
gueepo::Texture* duckTexture = nullptr;
gueepo::OrtographicCamera* cam;

// ================================================================================
// example of user defined layers
// ================================================================================
class ExampleLayer : public gueepo::Layer {
public:
	ExampleLayer() : Layer("MyLayer") {}

	void OnAttach() override {
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
		gueepo::Renderer::BeginScene(*cam);

		duckTexture->Bind();
		gueepo::Renderer::Submit(squareVA, squareShader);

		gueepo::Renderer::EndScene();
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

		cam = new gueepo::OrtographicCamera(2, 2);
		cam->SetBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f);
	}

	~DummyApp() { LOG_INFO("deleting dummy app"); }
};

// ================================================================================
// entry point
// ================================================================================
gueepo::Application* gueepo::CreateApplication() {
	return new DummyApp("dummy app!", 1024, 768);
}