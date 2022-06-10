#ifdef GUEEPO2D_SANDBOX

#include "Sandbox.h"

static gueepo::GameObject* s_player1 = nullptr;
static gueepo::GameObject* s_player4 = nullptr;

static gueepo::FontSprite* kenneyFutureSquare = nullptr;
static gueepo::FontSprite* kenneySpace = nullptr;
static gueepo::FontSprite* roboto = nullptr;
static gueepo::FontSprite* openSans = nullptr;
static gueepo::FontSprite* dogica = nullptr;

static gueepo::string fox("the quick brown fox\njumps over the lazy dog");

static float s_Count = 0.0f;
static int s_currentTile = 3;

void GameLayer::OnAttach() {
	GUEEPO2D_SCOPED_TIMER("sample layer initialization");
	// this shouldn't be here, the engine should initialize the renderer, not the game???
	gueepo::Renderer::Initialize();

	m_Camera = std::make_unique<gueepo::OrtographicCamera>(800, 600);
	m_Camera->SetBackgroundColor(0.0f, 0.0f, 0.0f, 1.0f);
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
	gueepo::Font* kenneySpaceFont = gueepo::Font::CreateFont("./assets/Fonts/Kenney Space.ttf");
	gueepo::Font* robotoFont = gueepo::Font::CreateFont("./assets/Fonts/Roboto-Black.ttf");
	gueepo::Font* openSansFont = gueepo::Font::CreateFont("./assets/fonts/static/OpenSans/OpenSans-Bold.ttf");
	gueepo::Font* dogicaFont = gueepo::Font::CreateFont("./assets/fonts/dogica.ttf");

	{
		GUEEPO2D_SCOPED_TIMER("creating fontsprite");
		dogica = new gueepo::FontSprite(dogicaFont, 16);
		dogica->SetLineGap(4);
		kenneyFutureSquare = new gueepo::FontSprite(kenneyFutureSquareFont, 32);
		kenneySpace = new gueepo::FontSprite(kenneySpaceFont, 32);
		roboto = new gueepo::FontSprite(robotoFont, 32);
		openSans = new gueepo::FontSprite(openSansFont, 32);
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
	gueepo::Renderer::BeginScene(*m_Camera);
	
	gueepo::Renderer::DrawText(dogica, fox, gueepo::math::vec2(-300.0f, 200.0f), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	gueepo::Renderer::DrawText(kenneyFutureSquare, fox, gueepo::math::vec2(-300.0f, 100.0f), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	// gueepo::Renderer::DrawText(kenneyFutureSquare, "the five boxing wizards jump quickly", gueepo::math::vec2(-300.0f, 100), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	// gueepo::Renderer::DrawText(kenneyFutureSquare, "Two driven jocks help fax my big quiz", gueepo::math::vec2(-300.0f, 50), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	// gueepo::Renderer::DrawText(kenneyFutureSquare, "Fickle jinx bog dwarves spy math quiz.", gueepo::math::vec2(-300.0f, 0), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	// gueepo::Renderer::DrawText(kenneyFutureSquare, "Pack my box with five dozen liquor jugs", gueepo::math::vec2(-300.0f, -50), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	// gueepo::Renderer::DrawText(kenneyFutureSquare, "When zombies arrive,", gueepo::math::vec2(-300.0f, -100), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	// gueepo::Renderer::DrawText(kenneyFutureSquare, "quickly fax judge Pat", gueepo::math::vec2(-300.0f, -125), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	// gueepo::Renderer::DrawText(kenneyFutureSquare, "The wizard quickly jinxed the ", gueepo::math::vec2(-300.0f, -175), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	// gueepo::Renderer::DrawText(kenneyFutureSquare, "gnomes before they vaporized", gueepo::math::vec2(-300.0f, -200), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));

	
	gueepo::Renderer::DrawText(roboto, fox, gueepo::math::vec2(-300.0f, -60.0f), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));

	gueepo::Renderer::DrawText(openSans, fox, gueepo::math::vec2(-300.0f, -160.0f), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	
	gueepo::Renderer::EndScene(); // SHOULD BE DONE BY THE ENGINE?! probably lol
}

#endif