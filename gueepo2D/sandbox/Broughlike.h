#pragma once
#include <gueepo2d.h>

class BroughlikeGameLayer : public gueepo::Layer {
public:
	BroughlikeGameLayer() : Layer("broughlike game layer") {}
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float DeltaTime) override;
	void OnInput(const gueepo::InputState& currentInputState) override;
	void OnEvent(gueepo::Event& e) override;
	void OnRender() override;
	void OnImGuiRender() override;
};

class Broughlike : public gueepo::Application {
public:
	Broughlike(const std::string& _Title, unsigned int _Width, unsigned int _Height) : Application(_Title, _Width, _Height) {
		PushLayer(new BroughlikeGameLayer());
	}

	Broughlike() : Broughlike("broughlike", 960, 540) {}

	~Broughlike() {}
};

// ================================================================================
// entry point
// ================================================================================
gueepo::Application* gueepo::CreateApplication() {
	return new Broughlike();
}