#include <gueepo2D.h>

static gueepo::GameObject* s_player1 = nullptr;
static gueepo::GameObject* s_player4 = nullptr;

static float s_Count = 0.0f;
static int s_currentTile = 3;

class GameLayer : public gueepo::Layer {
public:
	GameLayer() : Layer("sample layer") {}

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float DeltaTime) override;
	void OnInput(const gueepo::InputState& currentInputState) override {}
	void OnEvent(gueepo::Event& e) override {}
	void OnRender() override;
	void OnImGuiRender() override {}

private:
	std::unique_ptr<gueepo::OrtographicCamera> m_Camera;
	std::unique_ptr<gueepo::GameWorld> m_gameWorld;
	std::unique_ptr<gueepo::ResourceManager> m_resourceManager;
};

void GameLayer::OnAttach() {
	GUEEPO2D_SCOPED_TIMER("sample layer initialization");


	// this shouldn't be here, the engine should initialize the renderer, not the game???
	gueepo::Renderer::Initialize();

	m_Camera = std::make_unique<gueepo::OrtographicCamera>(960, 540);
	m_Camera->SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	m_gameWorld = std::make_unique<gueepo::GameWorld>();
	m_resourceManager = std::make_unique<gueepo::ResourceManager>();

	m_resourceManager->AddTexture("template-texture", "./assets/Template.png");
	m_resourceManager->AddTilemap("texture-tilemap", "template-texture");
	m_resourceManager->GetTilemap("texture-tilemap")->Slice(16, 16);

	// This uses the default sprite constructor, should draw the entire texture
	s_player1 = m_gameWorld->CreateGameObject(m_resourceManager->GetTexture("template-texture"), "Player");
	s_player1->SetPosition(0.0, 0.0f);
	s_player1->SetScale(3.0f, 3.0f);

	// This simulates using the sprite constructor that gives a Tile
	s_player4 = m_gameWorld->CreateGameObject(m_resourceManager->GetTexture("template-texture"), "Player4");
	s_player4->SetPosition(0.0f, 128.0f);
	s_player4->SetScale(3.0f, 3.0f);
	s_player4->sprite->RebuildFromTile(m_resourceManager->GetTilemap("texture-tilemap")->GetTile(7));
}

void GameLayer::OnDetach() {
	m_gameWorld->Destroy();
	m_resourceManager->ClearResources();
}

void GameLayer::OnUpdate(float DeltaTime) {

	s_Count += DeltaTime;

	if (s_Count >= 0.2f) {
		s_Count = 0.0f;
		s_currentTile = (s_currentTile + 4) % m_resourceManager->GetTilemap("texture-tilemap")->GetNumberOfTiles();

		s_player4->sprite->RebuildFromTile(m_resourceManager->GetTilemap("texture-tilemap")->GetTile(s_currentTile));
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