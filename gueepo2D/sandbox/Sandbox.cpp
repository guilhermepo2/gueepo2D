#ifdef GUEEPO2D_SANDBOX

#include "Sandbox.h"

static gueepo::GameObject* s_player1 = nullptr;
static gueepo::GameObject* s_player4 = nullptr;

static gueepo::Texture* myTex;

static float s_Count = 0.0f;
static int s_currentTile = 3;

void GameLayer::OnAttach() {
	GUEEPO2D_SCOPED_TIMER("sample layer initialization");
	// this shouldn't be here, the engine should initialize the renderer, not the game???
	gueepo::Renderer::Initialize();

	m_Camera = std::make_unique<gueepo::OrtographicCamera>(800, 600);
	m_Camera->SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
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

	gueepo::Font* myFont = gueepo::Font::CreateFont("./assets/Fonts/Kenney Future Square.ttf");

	int b_w = 512; /* bitmap width */
	int b_h = 128; /* bitmap height */
	int l_h = 52; /* line height */

	/* create a bitmap for the phrase */
	unsigned char* bitmap = (unsigned char*)calloc(b_w * b_h, sizeof(unsigned char));
	int bitmapSize = b_w * b_h * sizeof(unsigned char);

	/* calculate font scaling */
	float scale = myFont->GetScale(l_h);

	char* word = "the quick brown fox";
	int x = 0;

	 int i;
	 for (i = 0; i < strlen(word); ++i) {
		gueepo::Character ch = myFont->GetCharacter(word[i], scale);
	 	int y = myFont->GetAscent() * scale + ch.offset_y;
		int byteOffset = x + roundf(ch.offset_x * scale) + (y * b_w);
		unsigned char* src = bitmap + byteOffset;
		unsigned char** src2 = &src;
		myFont->BlitCharacter(ch, b_w, src2);
	 
	 	x += roundf(ch.advance * ch.scale);
	 	int kern;
		kern = myFont->GetKerning(word[i], word[i + 1], scale);
	 	x += roundf(kern);
	 }
	 
	 /* save out a 1 channel image */
	 myTex = gueepo::Texture::Create(b_w, b_h);
	 
	 unsigned char* bitmap2 = (unsigned char*)calloc(b_w * b_h, sizeof(unsigned char));
	 
	 int theY = 0;
	 for (int y = b_h - 1; y >= 0; y--) {
	 	for (int x = 0; x < b_w; x++) {
	 		bitmap2[(b_w * y) + x] = bitmap[(b_w * theY) + x];
	 	}
	 	theY += 1;
	 }

	myTex->SetData(bitmap2, bitmapSize);

	gueepo::g_SaveImage("out2.png", b_w, b_h, 1, bitmap, b_w);
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

	// pb->Render();
	gueepo::Renderer::Draw(myTex);
	// m_gameWorld->Render();
	// m_collisionWorld->Debug_Render();

	gueepo::Renderer::EndScene(); // SHOULD BE DONE BY THE ENGINE?! probably lol
}

#endif