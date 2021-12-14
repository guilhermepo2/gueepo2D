#include "Broughlike.h"

static gueepo::Texture* s_playerTexture = nullptr;
static gueepo::Texture* s_wallTexture = nullptr;
static gueepo::Texture* s_groundTexture = nullptr;

static gueepo::GameObject* m_playerObject;
// static std::vector<gueepo::GameObject> m_WallsAndFloor;

static gueepo::OrtographicCamera* cam;
static const float MOVEMENT_AMOUNT = 16.0f;

void BroughlikeGameLayer::OnAttach() {
	cam = new gueepo::OrtographicCamera(640, 360);
	cam->SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

	s_playerTexture = gueepo::Texture::Create("./assets/broughlike/player.png");
	s_wallTexture = gueepo::Texture::Create("./assets/broughlike/wall.png");
	s_groundTexture = gueepo::Texture::Create("./assets/broughlike/ground.png");

	m_playerObject = new gueepo::GameObject(s_playerTexture, "Player");
	m_playerObject->SetScale(2.0f, 2.0f);

	/*
	for (int i = -320; i < 320; i += 16) {
		for (int j = -180; j < 180; j += 16) {
			gueepo::GameObject temp(s_groundTexture);
			temp.SetPosition(gueepo::math::Vector2(i, j));
			m_WallsAndFloor.push_back(temp);
		}
	}
	*/
}

void BroughlikeGameLayer::OnDetach() {

}

void BroughlikeGameLayer::OnInput(const gueepo::InputState& currentInputState) {
	if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_W)) {
		m_playerObject->Translate(0.0f, MOVEMENT_AMOUNT);
	}
	else if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_S)) {
		m_playerObject->Translate(0.0f, -MOVEMENT_AMOUNT);
	}
	else if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_D)) {
		m_playerObject->Translate(MOVEMENT_AMOUNT, 0.0f);
	}
	else if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_A)) {
		m_playerObject->Translate(-MOVEMENT_AMOUNT, 0.0f);
	}
}

void BroughlikeGameLayer::OnUpdate(float DeltaTime) {
	unreferenced(DeltaTime);
}


void BroughlikeGameLayer::OnEvent(gueepo::Event& e) {
	unreferenced(e);
}

void BroughlikeGameLayer::OnRender() {
	// #todo: I don't like having this BeginScene() and EndScene() here
	// this should be abstracted in the engine (on an ECS system or something like that)
	gueepo::Renderer::BeginScene(*cam);

	m_playerObject->Render();
	gueepo::Renderer::EndScene();
}

void BroughlikeGameLayer::OnImGuiRender() {

}