#pragma once
#include "core/Common.h"
#include "core/Log.h"
#include "core/Application.h"

extern gueepo::Application* gueepo::CreateApplication();

#if 1
int main(int argc, char** argv) {
	unreferenced(argc);
	unreferenced(argv);

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
#endif

#if 0
// temporary shit, this is used on windows so we can hide the log window
// should run this only on WINDOWS and RELEASE builds
// also have to change project setting from console to Windows
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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
#endif
