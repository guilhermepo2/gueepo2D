#include <gueepo2D.h>

static gueepo::Texture* s_TemplateTexture = nullptr;
static gueepo::Tilemap* s_textureTilemap = nullptr;

static gueepo::GameObject* s_player1 = nullptr;
static gueepo::GameObject* s_player4 = nullptr;

static float s_Count = 0.0f;
static int s_currentTile = 3;

class GameLayer : public gueepo::Layer {
public:
	GameLayer() : Layer("sample layer") {}

	void OnAttach() override;
	void OnDetach() override {}
	void OnUpdate(float DeltaTime) override;
	void OnInput(const gueepo::InputState& currentInputState) override {}
	void OnEvent(gueepo::Event& e) override {}
	void OnRender() override;
	void OnImGuiRender() override {}

private:
	std::unique_ptr<gueepo::OrtographicCamera> m_Camera;
	std::unique_ptr<gueepo::GameWorld> m_gameWorld;
};

void GameLayer::OnAttach() {

	GUEEPO2D_SCOPED_TIMER("sample layer initialization");

	// this shouldn't be here, the engine should initialize the renderer, not the game???
	gueepo::Renderer::Initialize();

	m_Camera = std::make_unique<gueepo::OrtographicCamera>(960, 540);
	m_Camera->SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	s_TemplateTexture = gueepo::Texture::Create("./assets/Template.png");
	s_textureTilemap = gueepo::Tilemap::Create(s_TemplateTexture);
	s_textureTilemap->Slice(16, 16);

	m_gameWorld = std::make_unique<gueepo::GameWorld>();

	// This uses the default sprite constructor, should draw the entire texture
	s_player1 = m_gameWorld->CreateGameObject(s_TemplateTexture, "Player");
	s_player1->SetPosition(0.0, 0.0f);
	s_player1->SetScale(3.0f, 3.0f);

	// This simulates using the sprite constructor that gives a Tile
	s_player4 = m_gameWorld->CreateGameObject(s_TemplateTexture, "Player4");
	s_player4->SetPosition(0.0f, 128.0f);
	s_player4->SetScale(3.0f, 3.0f);
	s_player4->sprite->RebuildFromTile(s_textureTilemap->GetTile(7));
}

void GameLayer::OnUpdate(float DeltaTime) {

	s_Count += DeltaTime;

	if (s_Count >= 0.2f) {
		s_Count = 0.0f;
		s_currentTile = (s_currentTile + 4) % s_textureTilemap->GetNumberOfTiles();

		s_player4->sprite->RebuildFromTile(s_textureTilemap->GetTile(s_currentTile));
	}

	m_gameWorld->Update(DeltaTime);
}

void GameLayer::OnRender() {
	gueepo::Renderer::BeginScene(*m_Camera);

	m_gameWorld->Render();

	gueepo::Renderer::EndScene(); // SHOULD BE DONE BY THE ENGINE?! probably lol
}

class SandboxApp : public gueepo::Application {
public:
	
	SandboxApp() : Application("sandbox", 960, 540) {
		PushLayer(new GameLayer());
	}

	~SandboxApp() {}
};

gueepo::Application* gueepo::CreateApplication() {
	return new SandboxApp();
}