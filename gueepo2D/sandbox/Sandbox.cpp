#include <gueepo2D.h>

static gueepo::Texture* s_TemplateTexture = nullptr;
static gueepo::OrtographicCamera* s_Camera = nullptr;

static gueepo::GameObject* s_player1 = nullptr;
static gueepo::GameObject* s_player2 = nullptr;
static gueepo::GameObject* s_player3 = nullptr;

class SampleLayer : public gueepo::Layer {
public:
	SampleLayer() : Layer("sample layer") {}

	void OnAttach() override;
	void OnDetach() override {}
	void OnUpdate(float DeltaTime) override {}
	void OnInput(const gueepo::InputState& currentInputState) override {}
	void OnEvent(gueepo::Event& e) override {}
	void OnRender() override;
	void OnImGuiRender() override {}
};

void SampleLayer::OnAttach() {
	// this shouldn't be here, the engine should initialize the renderer, not the game???
	gueepo::Renderer::Initialize();

	s_Camera = new gueepo::OrtographicCamera(960, 540);
	s_Camera->SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	s_TemplateTexture = gueepo::Texture::Create("./assets/Template.png");

	// How would I represent a Tilemap? a Tile?
	// What is a Tilemap?

	// This uses the default sprite constructor, should draw the entire texture
	s_player1 = new gueepo::GameObject(s_TemplateTexture, "Player");
	s_player1->SetPosition(0.0, 0.0f);
	s_player1->SetScale(3.0f, 3.0f);

	// This simulates using the sprite constructor that gives a min and a max for the source rectangle
	s_player2 = new gueepo::GameObject(s_TemplateTexture, "Player");
	s_player2->SetPosition(200.0, 64.0f);
	s_player2->SetScale(3.0f, 3.0f);
	s_player2->sprite->RebuildSourceRectangle(gueepo::math::Vector2(16, 0), gueepo::math::Vector2(32, 16));

	// This simulates using the sprite constructor that gives tile position and tile size
	s_player3 = new gueepo::GameObject(s_TemplateTexture, "Player");
	s_player3->SetPosition(200.0, -64.0f);
	s_player3->SetScale(3.0f, 3.0f);
	s_player3->sprite->RebuildSourceRectangle(3, 3, 16, 16);
}

void SampleLayer::OnRender() {
	gueepo::Renderer::BeginScene(*s_Camera);

	s_player1->Render();
	s_player2->Render();
	s_player3->Render();

	gueepo::Renderer::EndScene(); // SHOULD BE DONE BY THE ENGINE?! probably lol
}

class SandboxApp : public gueepo::Application {
public:
	
	SandboxApp() : Application("sandbox", 960, 540) {
		PushLayer(new SampleLayer());
	}

	~SandboxApp() {}
};

gueepo::Application* gueepo::CreateApplication() {
	return new SandboxApp();
}