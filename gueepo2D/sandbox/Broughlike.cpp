#include "Broughlike.h"
#include <imgui.h>
#include "TileComponent.h"

static gueepo::Texture* s_playerTexture = nullptr;
static gueepo::Texture* s_wallTexture = nullptr;
static gueepo::Texture* s_groundTexture = nullptr;
static gueepo::GameObject* m_playerObject;

// map stuff
static const int TILE_SIZE = 16;
static const int TILE_HORIZONTAL = 9;
static const int TILE_VERTICAL = 9;
static std::vector<gueepo::GameObject*> m_WallsAndFloor;

static gueepo::OrtographicCamera* cam;
static const float MOVEMENT_AMOUNT = 16.0f;

gueepo::GameObject* GetRandomPassableTile();
bool IsTilePassable(float x, float y);

void BroughlikeGameLayer::OnAttach() {
	gueepo::Random::Init();

	cam = new gueepo::OrtographicCamera(320, 180);
	cam->SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
	cam->SetPosition(gueepo::math::Vector3(0.8f, 0.7f, 0.0f));

	s_playerTexture = gueepo::Texture::Create("./assets/broughlike/player.png");
	s_wallTexture = gueepo::Texture::Create("./assets/broughlike/wall.png");
	s_groundTexture = gueepo::Texture::Create("./assets/broughlike/ground.png");

	m_playerObject = new gueepo::GameObject(s_playerTexture, "Player");
	m_playerObject->SetScale(2.0f, 2.0f);

	m_WallsAndFloor.resize(TILE_HORIZONTAL * TILE_VERTICAL);
	for (int i = 0; i < TILE_HORIZONTAL; i++) {
		for (int j = 0; j < TILE_VERTICAL; j++) {
			gueepo::GameObject* temp = new gueepo::GameObject(s_groundTexture, "Ground");
			TileComponent& tile = temp->AddComponent<TileComponent>(i * TILE_SIZE, j * TILE_SIZE, true);

			if (i == 0 || j == 0 || i == TILE_HORIZONTAL - 1 || j == TILE_VERTICAL - 1) {
				temp->SetTexture(s_wallTexture);
				tile.SetPassable(false);
			}

			if (gueepo::Random::Float() < 0.2f) {
				temp->SetTexture(s_wallTexture);
				tile.SetPassable(false);
			}

			temp->SetScale(2.0f, 2.0f);
			temp->SetPosition(i * TILE_SIZE, j * TILE_SIZE);
			m_WallsAndFloor[ (i * TILE_HORIZONTAL) + j] = temp;
		}
	}

	// todo: habe to validate the dungeon

	gueepo::GameObject* startingTile = GetRandomPassableTile();
	m_playerObject->SetPosition(startingTile->transform->position);
}

void BroughlikeGameLayer::OnDetach() {

}

void BroughlikeGameLayer::OnInput(const gueepo::InputState& currentInputState) {
	gueepo::math::Vector2 FuturePosition(m_playerObject->transform->position);

	if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_W)) {
		FuturePosition.y += MOVEMENT_AMOUNT;
	}
	else if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_S)) {
		FuturePosition.y -= MOVEMENT_AMOUNT;
	}
	else if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_D)) {
		FuturePosition.x += MOVEMENT_AMOUNT;
	}
	else if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_A)) {
		FuturePosition.x -= MOVEMENT_AMOUNT;
	}

	if (IsTilePassable(FuturePosition.x, FuturePosition.y)) {
		m_playerObject->Translate(FuturePosition - m_playerObject->transform->position);
		// #todo: here is where I will process all enemies turns....
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

	for (gueepo::GameObject* tile : m_WallsAndFloor) {
		tile->Render();
	}

	m_playerObject->Render();
	gueepo::Renderer::EndScene();
}

void BroughlikeGameLayer::OnImGuiRender() {
	
}


// ---------------------------------------------
// Auxiliary
// ---------------------------------------------
gueepo::GameObject* GetRandomPassableTile() {
	int x = gueepo::math::abs(gueepo::Random::Int() % TILE_HORIZONTAL);
	int y = gueepo::math::abs(gueepo::Random::Int() % TILE_VERTICAL);
	gueepo::GameObject* tile = m_WallsAndFloor[(x * TILE_HORIZONTAL) + y];
	TileComponent* tilecomponent = tile->GetComponentOfType<TileComponent>();

	while (!tile->GetComponentOfType<TileComponent>()->passable) {
		x = gueepo::Random::Int() % TILE_HORIZONTAL;
		y = gueepo::Random::Int() % TILE_VERTICAL;
		tile = m_WallsAndFloor[(x * TILE_HORIZONTAL) + y];
	}

	return tile;
}

bool IsTilePassable(float x, float y) {
	for (gueepo::GameObject* tile : m_WallsAndFloor) {
		if (tile->GetComponentOfType<TileComponent>()->internalX == x &&
			tile->GetComponentOfType<TileComponent>()->internalY == y) {
			return tile->GetComponentOfType<TileComponent>()->passable;
		}
	}

	return false;
}