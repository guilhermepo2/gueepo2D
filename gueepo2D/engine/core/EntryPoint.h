#pragma once
#include "core/Common.h"
#include "core/Log.h"
#include "core/Application.h"

extern gueepo::Application* gueepo::CreateApplication();

int main(int argc, char** argv) {
	unreferenced(argc, argv);

	gueepo::Log::Initialize();
	LOG_INFO("log initialized");

	gueepo::Application* app = gueepo::CreateApplication();

	if (app != nullptr) {
		app->Run();
		delete app;
	}
	else {
		LOG_ERROR("why is app a nullptr?");
	}

	return 0;
}
