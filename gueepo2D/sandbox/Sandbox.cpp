#include <gueepo2D.h>

static const int WIDTH = 960;
static const int HEIGHT = 540;
static const int DATA_SIZE = WIDTH * HEIGHT * 4;

static gueepo::GameObject* s_player1 = nullptr;
static gueepo::GameObject* s_player4 = nullptr;
// static gueepo::Texture* s_tex = nullptr;
// static unsigned char* tex_data;

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
	std::unique_ptr<gueepo::CollisionWorld> m_collisionWorld;
};

void GameLayer::OnAttach() {
	GUEEPO2D_SCOPED_TIMER("sample layer initialization");


	// this shouldn't be here, the engine should initialize the renderer, not the game???
	gueepo::Renderer::Initialize();

	m_Camera = std::make_unique<gueepo::OrtographicCamera>(WIDTH, HEIGHT);
	m_Camera->SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	m_gameWorld = std::make_unique<gueepo::GameWorld>();
	m_resourceManager = std::make_unique<gueepo::ResourceManager>();
	m_collisionWorld = std::make_unique<gueepo::CollisionWorld>();
	m_collisionWorld->Initialize();

	m_resourceManager->AddTexture("template-texture", "./assets/Template.png");
	m_resourceManager->AddTilemap("texture-tilemap", "template-texture");
	m_resourceManager->GetTilemap("texture-tilemap")->Slice(16, 16);

	// s_tex = gueepo::Texture::Create("./assets/Template.png");
	// s_tex = gueepo::Texture::Create(WIDTH, HEIGHT);
	// tex_data = new unsigned char[DATA_SIZE];

	// unsigned char* texData = new unsigned char[300 * 300 * 4];
	// memset(texData, 255, 300 * 300 * 4);
	// s_tex->SetData(texData, 300 * 300 * 4);

	// This uses the default sprite constructor, should draw the entire texture
	s_player1 = m_gameWorld->CreateGameObject(m_resourceManager->GetTexture("template-texture"), "Player");
	s_player1->SetPosition(0.0, 0.0f);
	s_player1->SetScale(3.0f, 3.0f);
	s_player1->AddComponent<gueepo::BoxCollider>(gueepo::math::vec2(-16.0f, -16.0f), gueepo::math::vec2(16.0f, 16.0f));

	// This simulates using the sprite constructor that gives a Tile
	s_player4 = m_gameWorld->CreateGameObject(m_resourceManager->GetTexture("template-texture"), "Player4");
	s_player4->SetPosition(0.0f, 128.0f);
	s_player4->SetScale(3.0f, 3.0f);
	s_player4->sprite->RebuildFromTile(m_resourceManager->GetTilemap("texture-tilemap")->GetTile(7));
	s_player4->AddComponent<gueepo::BoxCollider>(gueepo::math::vec2(-8.0f, -8.0f), gueepo::math::vec2(8.0f, 8.0f));
}

void GameLayer::OnDetach() {
	m_gameWorld->Destroy();
	m_resourceManager->ClearResources();
}

void GameLayer::OnUpdate(float DeltaTime) {

	/*
	for (int i = 0; i < DATA_SIZE; i++) {
		tex_data[i] = gueepo::rand::Int() % 255;
	}
	s_tex->SetData(tex_data, DATA_SIZE);
	*/

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

	
	// gueepo::Renderer::Draw(s_tex);
	m_gameWorld->Render();
	m_collisionWorld->Debug_Render();

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