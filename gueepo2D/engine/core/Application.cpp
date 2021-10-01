#include "Application.h"
#include "Log.h"

namespace gueepo {

	Application::Application() {

	}

	Application::~Application()
	{

	}

	void Application::Run() {
		LOG_INFO("application is running!");
		while (true) {
			// calculate delta time
			// handle events
			// handle input
			// handle update
			// handle render
		}
	}

}
