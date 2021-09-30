#pragma once

namespace gueepo {
	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	// This is to be defined on the client
	Application* CreateApplication();
}
