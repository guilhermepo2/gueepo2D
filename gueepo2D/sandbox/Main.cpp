#include <gueepo2d.h>
#include <imgui.h>

gueepo::Shader* squareShader = nullptr;
gueepo::VertexArray* squareVA = nullptr;
gueepo::Texture* duckTexture = nullptr;
gueepo::OrtographicCamera* cam;
float backgroundColor[4];

gueepo::math::Matrix4 transform;
float xPos;
float yPos;
float scale = 16.0f;
float objScale = 1.0f;
float rotation;

class Transform {
public:
	gueepo::math::Vector2 position;
	float rotation;
	gueepo::math::Vector2 scale;

	Transform() {
		position = gueepo::math::Vector2(0.0f, 0.0f);
		rotation = 0.0f;
		scale = gueepo::math::Vector2(1.0f, 1.0f);
	}

	gueepo::math::Matrix4 GetTransformMatrix() {
		return gueepo::math::Matrix4::CreateScale(scale)
			* gueepo::math::Matrix4::CreateRotation(rotation * gueepo::math::DEG_TO_RAD)
			* gueepo::math::Matrix4::CreateTranslation(position);
	}
};

Transform duckTransform;

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
	}

	void OnDetach() override {}

	void OnUpdate(float DeltaTime) override {
		unreferenced(DeltaTime);

		duckTransform.position.x = xPos;
		duckTransform.position.y = yPos;
		duckTransform.rotation = rotation;
		duckTransform.scale.x = objScale;
		duckTransform.scale.y = objScale;
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
		cam->SetBackgroundColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
		gueepo::Renderer::BeginScene(*cam);

		duckTexture->Bind();
		gueepo::math::Matrix4 textureScale = gueepo::math::Matrix4::CreateScale(gueepo::math::Vector2(scale, scale));
		transform = textureScale * (duckTransform.GetTransformMatrix());
		squareShader->SetMat4("u_Transform", transform);
		gueepo::Renderer::Submit(squareVA, squareShader);

		gueepo::Renderer::EndScene();
	}

	void OnImGuiRender() { 
		ImGui::Begin("color");
		ImGui::ColorEdit4("clear color", backgroundColor);
		ImGui::DragFloat("xPos", &xPos, 1.0f, -500.0f, 500.0f);
		ImGui::DragFloat("yPos", &yPos, 1.0f, -500.0f, 500.0f);
		ImGui::DragFloat("tex scale", &scale, 1.0f, 16.0f, 256.0f);
		ImGui::DragFloat("obj scale", &objScale, 1.0f, 1.0f, 5.0f);
		ImGui::DragFloat("rotation", &rotation, 1.0f, 0.0f, 360.0f);
		ImGui::End();
	}
};

// ================================================================================
// application class
// ================================================================================
class DummyApp : public gueepo::Application {
public:
	
	DummyApp(const std::string& _Title, unsigned int _Width, unsigned int _Height) 
		: Application(_Title, _Width, _Height) {
		PushLayer(new ExampleLayer());

		cam = new gueepo::OrtographicCamera(1024, 768);
		cam->SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	}

	~DummyApp() { LOG_INFO("deleting dummy app"); }
};

// ================================================================================
// entry point
// ================================================================================
gueepo::Application* gueepo::CreateApplication() {
	return new DummyApp("dummy app!", 1024, 768);
}