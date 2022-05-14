#ifdef PIXEL_SANDBOX
#include "PixelSandbox.h"
#include <imgui.h>

static const int WIDTH = 800;
static const int HEIGHT = 600;
static const int DATA_SIZE = WIDTH * HEIGHT;

static gueepo::PixelBuffer* pixelBuffer = nullptr;

#define EMPTY 0
#define SAND_ID 1
#define WATER_ID 2
#define SMOKE_ID 3
uint32_t currentlySelectedParticle = 0;

#define PositionToIndex(x, y) ((WIDTH * y) + x)

typedef struct {
	uint8_t id = 0;
	float lifetime;
	// gueepo::math::vec2 velocity;
	uint32_t color = 0;
} cell_t;

static cell_t* s_all_cells;

bool is_empty_cell(uint32_t x, uint32_t y) {
	if (x < 0 || y < 0 || x >= WIDTH  || y >= HEIGHT) {
		return false;
	}

	return s_all_cells[PositionToIndex(x, y)].id == EMPTY;
}

void create_sand_particle(uint32_t x, uint32_t y) {
	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT) {
		return;
	}

	s_all_cells[PositionToIndex(x, y)].id = SAND_ID;
	s_all_cells[PositionToIndex(x, y)].color = 0xFF0000FF;
}

void create_water_particle(uint32_t x, uint32_t y) {
	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT) {
		return;
	}

	s_all_cells[PositionToIndex(x, y)].id = WATER_ID;
	s_all_cells[PositionToIndex(x, y)].color = 0xFFFF0000;
}

void create_smoke_particle(uint32_t x, uint32_t y) {
	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT) {
		return;
	}

	s_all_cells[PositionToIndex(x, y)].id = SMOKE_ID;
	s_all_cells[PositionToIndex(x, y)].color = 0xFF333333;
	s_all_cells[PositionToIndex(x, y)].lifetime = 2.0f;
}

void update_sand(uint32_t x, uint32_t y) {
	bool didWeMove = false;

	// checking if we can go down
	if (is_empty_cell(x, y - 1)) {
		// for now we just create another one and make this one empty
		// but if this ever goes somewhere, then we actually need to copy the structures
		create_sand_particle(x, y - 1);
		didWeMove = true;
	}
	else if (is_empty_cell(x - 1, y - 1)) {
		create_sand_particle(x - 1, y - 1);
		didWeMove = true;
	}
	else if (is_empty_cell(x + 1, y - 1)) {
		create_sand_particle(x + 1, y - 1);
		didWeMove = true;
	}

	if (didWeMove) {
		s_all_cells[PositionToIndex(x, y)].id = EMPTY;
	}
}

void update_smoke(uint32_t x, uint32_t y, float DeltaTime) {
	if (s_all_cells[PositionToIndex(x, y)].lifetime < 0.0f) {
		s_all_cells[PositionToIndex(x, y)].id = EMPTY;
		return;
	}

	
	s_all_cells[PositionToIndex(x, y)].lifetime -= DeltaTime;

	bool didWeMove = false;

	if (is_empty_cell(x, y + 1)) {
		create_smoke_particle(x, y + 1);
		didWeMove = true;
	}
	else if (is_empty_cell(x - 1, y + 1)) {
		create_smoke_particle(x - 1, y + 1);
		didWeMove = true;
	}
	else if (is_empty_cell(x + 1, y + 1)) {
		create_smoke_particle(x + 1, y + 1);
		didWeMove = true;
	}

	if (didWeMove) {
		s_all_cells[PositionToIndex(x, y)].id = EMPTY;
	}
}

void update_water(uint32_t x, uint32_t y) {
	bool didWeMove = false;

	if (is_empty_cell(x, y - 1)) {
		// for now we just create another one and make this one empty
		// but if this ever goes somewhere, then we actually need to copy the structures
		create_water_particle(x, y - 1);
		didWeMove = true;
	}
	else if (is_empty_cell(x - 1, y - 1)) {
		create_water_particle(x - 1, y - 1);
		didWeMove = true;
	}
	else if (is_empty_cell(x + 1, y - 1)) {
		create_water_particle(x + 1, y - 1);
		didWeMove = true;
	}
	else if (is_empty_cell(x + 1, y)) {
		create_water_particle(x + 1, y);
		didWeMove = true;
	}
	else if (is_empty_cell(x - 1, y)) {
		create_water_particle(x - 1, y);
		didWeMove = true;
	}

	if (didWeMove) {
		s_all_cells[PositionToIndex(x, y)].id = EMPTY;
	}
}

// ======================================================================================================
// ======================================================================================================
// Pixel Layer
// ======================================================================================================
// ======================================================================================================
class PixelLayer : public gueepo::Layer {
public:
	PixelLayer() : Layer("pixel layer") {}

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float DeltaTime) override;
	void OnInput(const gueepo::InputState& currentInputState) override;
	void OnEvent(gueepo::Event& e) override {}
	void OnRender() override;
	void OnImGuiRender() override;

private:
	std::unique_ptr<gueepo::OrtographicCamera> m_Camera;
};

void PixelLayer::OnAttach() {
	gueepo::Renderer::Initialize();
	m_Camera = std::make_unique<gueepo::OrtographicCamera>(WIDTH, HEIGHT);
	m_Camera->SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

	pixelBuffer = gueepo::PixelBuffer::Create(WIDTH, HEIGHT);

	s_all_cells = new cell_t[WIDTH * HEIGHT];
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		s_all_cells[i].id = EMPTY;
	}
}

void PixelLayer::OnDetach() {
	delete pixelBuffer;
	delete[] s_all_cells;
}

void PixelLayer::OnUpdate(float DeltaTime) {
	// Iterate through all the cells and update them
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			switch (s_all_cells[PositionToIndex(x, y)].id) {
			case SAND_ID:
				update_sand(x, y);
				break;
			case WATER_ID:
				update_water(x, y);
				break;
			case SMOKE_ID:
				update_smoke(x, y, DeltaTime);
				break;
			default:
				break;
			}
		}
	}
}

void PixelLayer::OnInput(const gueepo::InputState& currentInputState) {

	if (currentInputState.Mouse.IsMouseKeyDown(gueepo::MOUSE_RIGHT)) {
		gueepo::math::vec2 pos = currentInputState.Mouse.GetPosition();
		int pos_x = (int)pos.x;
		int pos_y = HEIGHT - (int)pos.y;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				switch (currentlySelectedParticle) {
				case SAND_ID:
					create_sand_particle(pos_x + i, pos_y + j);
					break;
				case WATER_ID:
					create_water_particle(pos_x + i, pos_y + j);
					break;
				case SMOKE_ID:
					create_smoke_particle(pos_x + i, pos_y + j);
					break;
				}
			}
		}
	}
}

void PixelLayer::OnRender() {
	gueepo::Renderer::BeginScene(*m_Camera);

	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			pixelBuffer->SetColor(x, y, 0xFF000000);
		}
	}


	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			cell_t currentCell = s_all_cells[PositionToIndex(x, y)];

			if (currentCell.id != EMPTY) {
				pixelBuffer->SetColor(x, y, currentCell.color);
			}
		}
	}

	pixelBuffer->Render();
	gueepo::Renderer::EndScene();
}

void PixelLayer::OnImGuiRender() {
	ImGui::Begin("Particle Selector");
	if (ImGui::Button("sand")) {
		currentlySelectedParticle = 1;
	}
	if (ImGui::Button("water")) {
		currentlySelectedParticle = 2;
	}
	if (ImGui::Button("smoke")) {
		currentlySelectedParticle = 3;
	}
	ImGui::End();
}

// =======================================================================
// =======================================================================

PixelApp::PixelApp() : Application("pixel app", WIDTH, HEIGHT) {
	PushLayer(new PixelLayer());
}
#endif