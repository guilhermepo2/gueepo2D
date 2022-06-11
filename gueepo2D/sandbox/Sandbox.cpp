#ifdef GUEEPO2D_SANDBOX

#include "Sandbox.h"

static gueepo::GameObject* s_player1 = nullptr;
static gueepo::GameObject* s_player4 = nullptr;

static gueepo::FontSprite* kenneyFutureSquare = nullptr;
static gueepo::FontSprite* dogica = nullptr;

static gueepo::string fox("the quick brown fox\njumps over the lazy dog");

static float s_Count = 0.0f;
static int s_currentTile = 3;

void GameLayer::OnAttach() {
	GUEEPO2D_SCOPED_TIMER("sample layer initialization");
	// this shouldn't be here, the engine should initialize the renderer, not the game???
	gueepo::Renderer::Initialize();

	m_Camera = std::make_unique<gueepo::OrtographicCamera>(800, 600);
	m_Camera->SetBackgroundColor(0.33f, 0.0f, 0.33f, 1.0f);
	m_gameWorld = std::make_unique<gueepo::GameWorld>();
	m_resourceManager = std::make_unique<gueepo::ResourceManager>();
	m_collisionWorld = std::make_unique<gueepo::CollisionWorld>();
	m_collisionWorld->Initialize();

	m_resourceManager->AddTexture("template-texture", "./assets/Template.png");
	m_resourceManager->AddTilemap("texture-tilemap", "template-texture");
	m_resourceManager->GetTilemap("texture-tilemap")->Slice(16, 16);

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

	// =========================================================================
	// =========================================================================
	// trying this font thing!
	// =========================================================================
	// =========================================================================
	gueepo::Font* kenneyFutureSquareFont = gueepo::Font::CreateFont("./assets/Fonts/Kenney Future Square.ttf");
	gueepo::Font* dogicaFont = gueepo::Font::CreateFont("./assets/fonts/dogica.ttf");

	{
		GUEEPO2D_SCOPED_TIMER("creating fontsprite");
		dogica = new gueepo::FontSprite(dogicaFont, 16);
		dogica->SetLineGap(4);
		kenneyFutureSquare = new gueepo::FontSprite(kenneyFutureSquareFont, 32);
	}

}

void GameLayer::OnDetach() {
	m_gameWorld->Destroy();
	m_resourceManager->ClearResources();
}

void GameLayer::OnInput(const gueepo::InputState& currentInputState) {
	
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
	gueepo::Renderer::Begin(*m_Camera);

	gueepo::Renderer::s_spriteBatcher->Begin(*m_Camera);
	m_gameWorld->Render();
	gueepo::Renderer::s_spriteBatcher->End();
	
	gueepo::Renderer::s_uiBatcher->Begin(*m_Camera);
	gueepo::Renderer::s_uiBatcher->DrawText(dogica, "this engine now render fonts", gueepo::math::vec2(-350.0f, -250.0f), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	gueepo::Renderer::s_uiBatcher->DrawText(kenneyFutureSquare, "it's pretty cool", gueepo::math::vec2(-350.0f, -275.0f), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	gueepo::Renderer::s_uiBatcher->End();

	gueepo::Renderer::End();
}

#endif