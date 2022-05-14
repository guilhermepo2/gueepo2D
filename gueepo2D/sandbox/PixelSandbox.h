#pragma once
#ifdef PIXEL_SANDBOX

#include <gueepo2d.h>

class PixelApp : public gueepo::Application {
public:

	PixelApp();
	~PixelApp() {}
};

gueepo::Application* gueepo::CreateApplication() {
	return new PixelApp();
}

#endif