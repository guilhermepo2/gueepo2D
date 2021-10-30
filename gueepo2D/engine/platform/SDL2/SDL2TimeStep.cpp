#include "gueepo2Dpch.h"
#include "core/TimeStep.h"
#include <SDL.h>

namespace gueepo::timestep {
	uint32_t GetTicks() {
		return SDL_GetTicks();
	}

	void Sleep(int milliseconds) {
		SDL_Delay(milliseconds);
	}
}