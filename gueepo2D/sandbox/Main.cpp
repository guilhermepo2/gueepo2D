#include <gueepo2d.h>

// ================================================================================
// example of user defined layers
// ================================================================================
class ExampleLayer : public gueepo::Layer {
public:
	ExampleLayer() : Layer("MyLayer") {}

	void OnUpdate(float DeltaTime) override {
		unreferenced(DeltaTime);
	}

	void OnEvent(gueepo::Event& e) override {
		unreferenced(e);
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
		PushOverlay(new gueepo::ImGuiLayer());
	}

	~DummyApp() { LOG_INFO("deleting dummy app"); }
};

// ================================================================================
// entry point
// ================================================================================
gueepo::Application* gueepo::CreateApplication() {
	return new DummyApp("dummy app!", 640, 360);
}