#include <gueepo2D.h>

static gueepo::Texture* s_TemplateTexture = nullptr;
static gueepo::OrtographicCamera* s_Camera = nullptr;

typedef struct {
	gueepo::Texture* tex;
	gueepo::math::Vector2 SourceRectMin;
	gueepo::math::Vector2 SourceRectMax;

	gueepo::math::Vector2 GetSize() {
		return SourceRectMax - SourceRectMin;
	}

	gueepo::math::Vector2 GetCoordMin() {
		return gueepo::math::Vector2(
			SourceRectMin.x / tex->GetWidth(), 
			SourceRectMin.y / tex->GetHeight()
		);
	}

	gueepo::math::Vector2 GetCoordMax() {
		return gueepo::math::Vector2(
			SourceRectMax.x / tex->GetWidth(),
			SourceRectMax.y / tex->GetHeight()
		);
	}
} t_subtexture;

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

	gueepo::String myString("Jalapeno Poppers");
	LOG_INFO("{0}", myString.GetCRCValue());
}

void SampleLayer::OnRender() {
	gueepo::Renderer::BeginScene(*s_Camera); // SHOULD BE DONE BY THE ENGINE?! // it should be done by the engine.

	gueepo::math::Vector2 textureScale = gueepo::math::Vector2(s_TemplateTexture->GetWidth() * 2, s_TemplateTexture->GetHeight() * 2);
	gueepo::math::Matrix4 textureScaleMatrix = gueepo::math::Matrix4::CreateScale(textureScale);

	t_subtexture mySprite;
	mySprite.tex = s_TemplateTexture;

#if 1
	// Option 1. Setting hard positions for coordinates
	mySprite.SourceRectMin.x = 16;
	mySprite.SourceRectMin.y = 32;
	mySprite.SourceRectMax.x = 32;
	mySprite.SourceRectMax.y = 48;
#else
	// Option 2. Based on tile position and tile size
	int tile_x = 1;
	int tile_y = 2;
	int TileWidth = 16;
	int TileHeight = 16;

	mySprite.SourceRectMin.x = tile_x * TileWidth;
	mySprite.SourceRectMin.y = tile_y * TileHeight;
	mySprite.SourceRectMax.x = (tile_x + 1) * TileWidth;
	mySprite.SourceRectMax.y = (tile_y + 1) * TileHeight;
#endif

	// Subtexture(Texture* tex, Rect sourceRect)							-> SourceRectangle will be used to calculate TextureCoordinates
	// Subtexture(Texture* tex, Vector2 TilePosition, Vector2 TileSize)		-> TilePosition and TileSize are used to calculate SourceRect (vec2 min and vec2 max)

	gueepo::Renderer::Draw(gueepo::math::Matrix4::CreateScale(mySprite.GetSize() * 5), mySprite.GetCoordMin(), mySprite.GetCoordMax(), mySprite.tex);

	gueepo::Renderer::EndScene(); // SHOULD BE DONE BY THE ENGINE?!
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