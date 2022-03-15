#include <gueepo2D.h>

static gueepo::Texture* s_TemplateTexture = nullptr;
static gueepo::OrtographicCamera* s_Camera = nullptr;

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
}

void SampleLayer::OnRender() {
	gueepo::Renderer::BeginScene(*s_Camera); // SHOULD BE DONE BY THE ENGINE?!

	gueepo::math::Vector2 textureScale = gueepo::math::Vector2(s_TemplateTexture->GetWidth() * 2, s_TemplateTexture->GetHeight() * 2);
	gueepo::math::Matrix4 textureScaleMatrix = gueepo::math::Matrix4::CreateScale(textureScale);
	
	// TEMPORARY
	int tile_x = 0;
	int tile_y = 3;
	int TileWidth = 16;
	int TileHeight = 16;
	float tw = (float)TileWidth / s_TemplateTexture->GetWidth();
	float th = (float)TileHeight / s_TemplateTexture->GetHeight();

	float min_x = tile_x * tw;
	float min_y = tile_y * th;
	float max_x = (tile_x + 1) * tw;
	float max_y = (tile_y + 1) * th;

	gueepo::math::Vector2 coordMin = gueepo::math::Vector2(min_x, min_y);
	gueepo::math::Vector2 coordMax = gueepo::math::Vector2(max_x, max_y);

	gueepo::Renderer::Draw(textureScaleMatrix, coordMin, coordMax, s_TemplateTexture);

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