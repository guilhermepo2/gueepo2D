#include <gueepo2d.h>
#include <imgui.h>

// ================================================================================
// Test Functions
void TestLoadSaveImage();

// ================================================================================
// example of user defined layers
// ================================================================================
class ExampleLayer : public gueepo::Layer {
public:
	ExampleLayer() : Layer("MyLayer") {}

	void OnUpdate(float DeltaTime) override {
		unreferenced(DeltaTime);
	}

	void OnInput(const gueepo::InputState& currentInputState) {
		if (currentInputState.Mouse.WasMouseKeyPressedThisFrame(gueepo::Mousecode::MOUSE_LEFT)) {
			LOG_INFO("Mouse Button Pressed!");
		}
	}

	void OnEvent(gueepo::Event& e) override {
		unreferenced(e);
	}

	void OnImGuiRender() {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}
};

// ================================================================================
// application class
// ================================================================================
class DummyApp : public gueepo::Application {
public:
	
	DummyApp(const std::string& _Title, unsigned int _Width, unsigned int _Height) 
		: Application(_Title, _Width, _Height) {
		PushLayer(new ExampleLayer());
		TestLoadSaveImage();
	}

	~DummyApp() { LOG_INFO("deleting dummy app"); }
};

// ================================================================================
// entry point
// ================================================================================
gueepo::Application* gueepo::CreateApplication() {
	return new DummyApp("dummy app!", 1024, 768);
}

// ================================================================================
// ================================================================================
//	TEST FUNCTIONS
// ================================================================================
// ================================================================================

void TestLoadSaveImage() {
	int w;
	int h;
	int comp;
	unsigned char* image = gueepo::g_LoadImage("assets/whataweek.png", w, h, comp);
	gueepo::g_SaveImage("assets/whataweek2.png", w, h, comp, image);
	gueepo::g_FreeImage(image);
}