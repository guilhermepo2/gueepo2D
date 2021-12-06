/*
#include <imgui.h>
#include "GameObject.h"
#include "Broughlike.h"
*/

/*
gueepo::Shader* squareShader = nullptr;
gueepo::VertexArray* squareVA = nullptr;
gueepo::Texture* duckTexture = nullptr;
gueepo::OrtographicCamera* cam;
float backgroundColor[4];
GameObject duck1;
GameObject duck2;

// ================================================================================
// example of user defined layers
// ================================================================================
class ExampleLayer : public gueepo::Layer {
public:
	ExampleLayer() : Layer("MyLayer") {}

	void OnAttach() override {
		squareShader = gueepo::Shader::CreateFromFile("./assets/shaders/sprite.vertex", "./assets/shaders/sprite.fragment");
		duckTexture = gueepo::Texture::Create("./assets/duck_brown.png");

		float squareVertices[5 * 4] = {
			 -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
			 -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

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

		duck1.SetPosition(gueepo::math::Vector2(200.0f, 50.0f));
		duck1.SetTexture(duckTexture);
		duck2.SetPosition(gueepo::math::Vector2(-200.0f, -50.0f));
		duck2.SetTexture(duckTexture);
	}

	void OnDetach() override {}

	void OnUpdate(float DeltaTime) override {
		unreferenced(DeltaTime);
	}

	void OnInput(const gueepo::InputState& currentInputState) {
		unreferenced(currentInputState);
	}

	void OnEvent(gueepo::Event& e) override {
		unreferenced(e);
	}

	virtual void OnRender() {
		cam->SetBackgroundColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
		gueepo::Renderer::BeginScene(*cam);
		duck1.Render(squareShader, squareVA);
		duck2.Render(squareShader, squareVA);
		gueepo::Renderer::EndScene();
	}

	void OnImGuiRender() {  }
};

// ================================================================================
// application class
// ================================================================================
class DummyApp : public gueepo::Application {
public:
	
	DummyApp(const std::string& _Title, unsigned int _Width, unsigned int _Height) 
		: Application(_Title, _Width, _Height) {
		PushLayer(new ExampleLayer());

		cam = new gueepo::OrtographicCamera(640, 360);
		cam->SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	}

	~DummyApp() { LOG_INFO("deleting dummy app"); }
};
*/