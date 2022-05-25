#ifdef GUEEPO2D_SANDBOX

#include "Sandbox.h"

#pragma warning(push, 0)
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#pragma warning(pop)

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

	// trying this font thing!
	gueepo::File myFont("./assets/fonts/Kenney Future Square.ttf");
	size_t myFontSize = myFont.GetStringContent().size();
	size_t myFontLength = myFont.GetStringContent().length();

	// 1. loading font file?! have to make it use gueepo::File instead
	FILE* fontFile = fopen("./assets/fonts/Kenney Future Square.ttf", "rb");
	fseek(fontFile, 0, SEEK_END);
	long size = ftell(fontFile); // get how long is the file (22884 for Kenney Future Square)
	fseek(fontFile, 0, SEEK_SET); // reset

	unsigned char* fontBuffer = (unsigned char*)malloc(size);
	fread(fontBuffer, size, 1, fontFile);
	fclose(fontFile);

	stbtt_fontinfo info;
	if (!stbtt_InitFont(&info, fontBuffer, 0)) {
		LOG_WARN("failed to load font!!");
	}
	else {
		LOG_INFO("loaded font!");
	}

	int b_w = 512; /* bitmap width */
	int b_h = 128; /* bitmap height */
	int l_h = 52; /* line height */

	/* create a bitmap for the phrase */
	unsigned char* bitmap = (unsigned char*)calloc(b_w * b_h, sizeof(unsigned char));
	int bitmapSize = b_w * b_h * sizeof(unsigned char);

	/* calculate font scaling */
	float scale = stbtt_ScaleForPixelHeight(&info, l_h);

	char* word = "the quick brown fox";
	int x = 0;

	int ascent, descent, lineGap;
	stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);
	ascent = roundf(ascent * scale);
	descent = roundf(descent * scale);

	int i;
	for (i = 0; i < strlen(word); ++i)
	{
		/* how wide is this character */
		int ax;
		int lsb;
		stbtt_GetCodepointHMetrics(&info, word[i], &ax, &lsb);
		/* (Note that each Codepoint call has an alternative Glyph version which caches the work required to lookup the character word[i].) */

		/* get bounding box for character (may be offset to account for chars that dip above or below the line) */
		int c_x1, c_y1, c_x2, c_y2;
		stbtt_GetCodepointBitmapBox(&info, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

		/* compute y (different characters have different heights) */
		int y = ascent + c_y1;

		/* render character (stride and offset is important here) */
		int byteOffset = x + roundf(lsb * scale) + (y * b_w);
		stbtt_MakeCodepointBitmap(&info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

		/* advance x */
		x += roundf(ax * scale);

		/* add kerning */
		int kern;
		kern = stbtt_GetCodepointKernAdvance(&info, word[i], word[i + 1]);
		x += roundf(kern * scale);
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

	gueepo::g_SaveImage("out.png", b_w, b_h, 1, bitmap, b_w);
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