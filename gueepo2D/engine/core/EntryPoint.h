#pragma once
#include "core/Common.h"
#include "core/Log.h"
#include "core/Application.h"

extern gueepo::Application* gueepo::CreateApplication();

int main(int argc, char** argv) {
	unref(argc, argv);

	gueepo::Log::Initialize();
	LOG_INFO("log initialized");

	gueepo::Application* app = gueepo::CreateApplication();
	app->Run();
	delete app;

	return 0;
}
