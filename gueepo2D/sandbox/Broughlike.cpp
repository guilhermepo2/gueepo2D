#include "Broughlike.h"
#include "GameObject.h"

static gueepo::Texture* s_playerTexture = nullptr;
static gueepo::Texture* s_wallTexture = nullptr;
static gueepo::Texture* s_groundTexture = nullptr;

static GameObject m_playerObject;
static std::vector<GameObject> m_WallsAndFloor;

static gueepo::Shader* spriteShader = nullptr;
static gueepo::VertexArray* spriteVertexArray = nullptr;
static gueepo::OrtographicCamera* cam;
static const float MOVEMENT_AMOUNT = 16.0f;

static float spriteVertices[5 * 4] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
};

static unsigned int spriteIndices[6] = { 0, 1, 2, 2, 3, 0 };

void BroughlikeGameLayer::OnAttach() {
	cam = new gueepo::OrtographicCamera(640, 360);
	cam->SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

	spriteShader = gueepo::Shader::CreateFromFile("./assets/shaders/sprite.vertex", "./assets/shaders/sprite.fragment");
	s_playerTexture = gueepo::Texture::Create("./assets/broughlike/player.png");
	s_wallTexture = gueepo::Texture::Create("./assets/broughlike/wall.png");
	s_groundTexture = gueepo::Texture::Create("./assets/broughlike/ground.png");

	m_playerObject.SetTexture(s_playerTexture);

	for (int i = -320; i < 320; i += 16) {
		for (int j = -180; j < 180; j += 16) {
			GameObject temp;
			temp.SetPosition(gueepo::math::Vector2(i, j));
			temp.SetTexture(s_groundTexture);
			m_WallsAndFloor.push_back(temp);
		}
	}

	spriteVertexArray = gueepo::VertexArray::Create();

	gueepo::VertexBuffer* squareVB = gueepo::VertexBuffer::Create(spriteVertices, sizeof(spriteVertices));

	{
		gueepo::BufferLayout layout = {
			{ gueepo::ShaderDataType::Float3, "a_Position"},
			{ gueepo::ShaderDataType::Float2, "a_TexCoord"}
		};
		squareVB->SetLayout(layout);
	}
	spriteVertexArray->AddVertexBuffer(squareVB);


	gueepo::IndexBuffer* sq_IndexBuffer = gueepo::IndexBuffer::Create(spriteIndices, 6);
	spriteVertexArray->SetIndexBuffer(sq_IndexBuffer);
	spriteVertexArray->Unbind();
}

void BroughlikeGameLayer::OnDetach() {

}

void BroughlikeGameLayer::OnInput(const gueepo::InputState& currentInputState) {
	if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_W)) {
		m_playerObject.Translate(0.0f, MOVEMENT_AMOUNT);
	}
	else if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_S)) {
		m_playerObject.Translate(0.0f, -MOVEMENT_AMOUNT);
	}
	else if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_D)) {
		m_playerObject.Translate(MOVEMENT_AMOUNT, 0.0f);
	}
	else if (currentInputState.Keyboard.WasKeyPressedThisFrame(gueepo::Keycode::KEYCODE_A)) {
		m_playerObject.Translate(-MOVEMENT_AMOUNT, 0.0f);
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

	for (int i = 0; i < m_WallsAndFloor.size(); i++) {
		m_WallsAndFloor[i].Render(spriteShader, spriteVertexArray);
	}

	m_playerObject.Render(spriteShader, spriteVertexArray);
	gueepo::Renderer::EndScene();
}

void BroughlikeGameLayer::OnImGuiRender() {

}