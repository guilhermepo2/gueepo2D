#ifdef GUEEPO2D_SANDBOX

#include "Sandbox.h"

static gueepo::GameObject* s_player1 = nullptr;
static gueepo::GameObject* s_player4 = nullptr;

static gueepo::FontSprite* kenneyFutureSquare = nullptr;
static gueepo::FontSprite* kenneySpace = nullptr;
static gueepo::FontSprite* roboto = nullptr;
static gueepo::FontSprite* openSans = nullptr;

static gueepo::Texture* kenneyFutureSquareTex = nullptr;
static gueepo::Texture* kenneySpaceTex = nullptr;
static gueepo::Texture* robotoTex = nullptr;
static gueepo::Texture* openSansTex = nullptr;

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

	{
		GUEEPO2D_SCOPED_TIMER("creating fontsprite");
		kenneyFutureSquare = new gueepo::FontSprite(kenneyFutureSquareFont, 32);
		kenneySpace = new gueepo::FontSprite(kenneySpaceFont, 32);
		roboto = new gueepo::FontSprite(robotoFont, 32);
		openSans = new gueepo::FontSprite(openSansFont, 32);
	}

	/* ======================================================================= */
	// Making a texture with the words to compare the FontSprite* to
	// 
	// 
	// Kenney Future Square
	int b_w = 1024;
	int b_h = 128;
	int l_h = 32;
	unsigned char* bitmap = (unsigned char*)calloc(b_w * b_h, sizeof(unsigned char));
	int bitmapSize = b_w * b_h * sizeof(unsigned char);
	float f_scale = kenneyFutureSquareFont->GetScale(l_h);
	char* word = "the quick brown fox";
	int x = 0;
	int i;
	for (i = 0; i < strlen(word); ++i) {
		int glyph = kenneyFutureSquareFont->GetGlyphIndex(word[i]);
		int next = openSansFont->GetGlyphIndex(word[i + 1]);

		gueepo::Character ch = kenneyFutureSquareFont->GetCharacter(glyph, f_scale);
		int y = kenneyFutureSquareFont->GetAscent() * ch.scale + ch.offset.y;
		int byteOffset = x + roundf(ch.offset.x * f_scale) + (y * b_w);
		unsigned char* src = bitmap + byteOffset;
		unsigned char** src2 = &src;
		kenneyFutureSquareFont->BlitCharacter(ch, b_w, src2);

		x += roundf(ch.advance * ch.scale);
		int kern;
		kern = kenneyFutureSquareFont->GetGlyphKerning(glyph, next, f_scale);
		x += roundf(kern);
	}
	kenneyFutureSquareTex = gueepo::Texture::Create(b_w, b_h);
	unsigned char* bitmap2 = (unsigned char*)calloc(b_w * b_h, sizeof(unsigned char));

	int theY = 0;
	for (int y = b_h - 1; y >= 0; y--) {
		for (int x = 0; x < b_w; x++) {
			bitmap2[(b_w * y) + x] = bitmap[(b_w * theY) + x];
		}
		theY += 1;
	}

	kenneyFutureSquareTex->SetData(bitmap2, bitmapSize);

	// Kenney Space
	memset(bitmap, 0, b_w * b_h);
	memset(bitmap2, 0, b_w * b_h);
	f_scale = kenneySpaceFont->GetScale(l_h);
	x = 0;
	for (i = 0; i < strlen(word); ++i) {
		int glyph = kenneySpaceFont->GetGlyphIndex(word[i]);
		int next = openSansFont->GetGlyphIndex(word[i + 1]);

		gueepo::Character ch = kenneySpaceFont->GetCharacter(glyph, f_scale);
		int y = kenneySpaceFont->GetAscent() * ch.scale + ch.offset.y;
		int byteOffset = x + roundf(ch.offset.x * f_scale) + (y * b_w);
		unsigned char* src = bitmap + byteOffset;
		unsigned char** src2 = &src;
		kenneySpaceFont->BlitCharacter(ch, b_w, src2);

		x += roundf(ch.advance * ch.scale);
		int kern;
		kern = kenneySpaceFont->GetGlyphKerning(glyph, next, f_scale);
		x += roundf(kern);
	}

	theY = 0;
	for (int y = b_h - 1; y >= 0; y--) {
		for (int x = 0; x < b_w; x++) {
			bitmap2[(b_w * y) + x] = bitmap[(b_w * theY) + x];
		}
		theY += 1;
	}

	kenneySpaceTex = gueepo::Texture::Create(b_w, b_h);
	kenneySpaceTex->SetData(bitmap2, bitmapSize);

	// Roboto
	memset(bitmap, 0, b_w * b_h);
	memset(bitmap2, 0, b_w * b_h);
	f_scale = robotoFont->GetScale(l_h);
	x = 0;
	for (i = 0; i < strlen(word); ++i) {
		int glyph = robotoFont->GetGlyphIndex(word[i]);
		int next = openSansFont->GetGlyphIndex(word[i + 1]);

		gueepo::Character ch = robotoFont->GetCharacter(glyph, f_scale);
		int y = robotoFont->GetAscent() * ch.scale + ch.offset.y;
		int byteOffset = x + roundf(ch.offset.x * f_scale) + (y * b_w);
		unsigned char* src = bitmap + byteOffset;
		unsigned char** src2 = &src;
		robotoFont->BlitCharacter(ch, b_w, src2);

		x += roundf(ch.advance * ch.scale);
		int kern;
		kern = robotoFont->GetGlyphKerning(glyph, next, f_scale);
		x += roundf(kern);
	}

	theY = 0;
	for (int y = b_h - 1; y >= 0; y--) {
		for (int x = 0; x < b_w; x++) {
			bitmap2[(b_w * y) + x] = bitmap[(b_w * theY) + x];
		}
		theY += 1;
	}

	robotoTex = gueepo::Texture::Create(b_w, b_h);
	robotoTex->SetData(bitmap2, bitmapSize);

	// Open Sans
	memset(bitmap, 0, b_w * b_h);
	memset(bitmap2, 0, b_w * b_h);
	f_scale = openSansFont->GetScale(l_h);
	x = 0;
	for (i = 0; i < strlen(word); ++i) {
		int glyph = openSansFont->GetGlyphIndex(word[i]);
		int next = openSansFont->GetGlyphIndex(word[i + 1]);

		gueepo::Character ch = openSansFont->GetCharacter(glyph, f_scale);
		int y = openSansFont->GetAscent() * ch.scale + ch.offset.y;
		int byteOffset = x + roundf(ch.offset.x * f_scale) + (y * b_w);
		unsigned char* src = bitmap + byteOffset;
		unsigned char** src2 = &src;
		openSansFont->BlitCharacter(ch, b_w, src2);

		x += roundf(ch.advance * ch.scale);
		int kern;
		kern = openSansFont->GetGlyphKerning(glyph, next, f_scale);
		x += roundf(kern);
	}

	theY = 0;
	for (int y = b_h - 1; y >= 0; y--) {
		for (int x = 0; x < b_w; x++) {
			bitmap2[(b_w * y) + x] = bitmap[(b_w * theY) + x];
		}
		theY += 1;
	}

	openSansTex = gueepo::Texture::Create(b_w, b_h);
	openSansTex->SetData(bitmap2, bitmapSize);
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
	// gueepo::Renderer::DrawText(kenneyFutureSquare, "Kenney Future Square", gueepo::math::vec2(-250.0f, 100.0f), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	gueepo::Renderer::Draw(gueepo::math::vec2(200.0f, 200.0f), kenneyFutureSquareTex);
	gueepo::Renderer::DrawText(kenneyFutureSquare, "the quick brown fox", gueepo::math::vec2(-300.0f, 200.0f), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));

	gueepo::Renderer::Draw(gueepo::math::vec2(200.0f, 100.0f), kenneySpaceTex);
	gueepo::Renderer::DrawText(kenneySpace, "the quick brown fox", gueepo::math::vec2(-300.0f, 75.0f), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	
	gueepo::Renderer::Draw(gueepo::math::vec2(200.0f, -50.0f), robotoTex);
	gueepo::Renderer::DrawTextA(roboto, "the quick brown fox", gueepo::math::vec2(-300.0f, -60.0f), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	gueepo::Renderer::Draw(gueepo::math::vec2(200.0f, -150.0f), openSansTex);
	gueepo::Renderer::DrawTextA(openSans, "the quick brown fox", gueepo::math::vec2(-300.0f, -160.0f), 1.0f, gueepo::Color(1.0f, 1.0f, 1.0f, 1.0f));
	gueepo::Renderer::EndScene(); // SHOULD BE DONE BY THE ENGINE?! probably lol
}

#endif