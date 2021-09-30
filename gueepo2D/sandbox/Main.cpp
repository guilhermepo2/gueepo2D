#include <gueepo2d.h>

/*
#include <SDL.h>
#ifdef main
#undef main
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
*/

class DummyApp : public gueepo::Application {
public:
	DummyApp() {}
	~DummyApp() { LOG_INFO("deleting dummy app"); }
};

gueepo::Application* gueepo::CreateApplication() {
	return new DummyApp();
}

/*
int main(void) {
	
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG_ERROR("could not initialize sdl2: {0}", SDL_GetError());
		return 1;
	}
	window = SDL_CreateWindow(
		"hello_sdl2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		LOG_ERROR("could not create window: {0}", SDL_GetError());
		return 1;
	}
	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
*/