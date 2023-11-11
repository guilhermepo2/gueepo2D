#pragma once
#include "core/input/Input.h"
#include <SDL_gamecontroller.h>

namespace gueepo {

	class SDL2Input : public InputSystem {
	protected:
		bool Implementation_Initialize() override;
		void Implementation_Shutdown() override;
		void Implementation_PrepareForUpdate() override;
		void Implementation_Update() override;
		void Implementation_SetRelativeMouseMode(bool Value) override;

		SDL_GameController* m_Controller;
	};
}