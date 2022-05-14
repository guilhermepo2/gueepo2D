#pragma once
#ifdef GUEEPO2D_SANDBOX

#include <gueepo2d.h>

class GameLayer : public gueepo::Layer {
public:
	GameLayer() : Layer("sample layer") {}

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float DeltaTime) override;
	void OnInput(const gueepo::InputState& currentInputState) override;
	void OnEvent(gueepo::Event& e) override {}
	void OnRender() override;
	void OnImGuiRender() override {}

private:
	std::unique_ptr<gueepo::OrtographicCamera> m_Camera;
	std::unique_ptr<gueepo::GameWorld> m_gameWorld;
	std::unique_ptr<gueepo::ResourceManager> m_resourceManager;
	std::unique_ptr<gueepo::CollisionWorld> m_collisionWorld;
};

class SandboxApp : public gueepo::Application {
public:

	SandboxApp() : Application("sandbox", 800, 600) {
		PushLayer(new GameLayer());
	}

	~SandboxApp() {}
};

gueepo::Application* gueepo::CreateApplication() {
	return new SandboxApp();
}

#endif
