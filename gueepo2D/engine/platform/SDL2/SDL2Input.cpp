#include "SDL2Input.h"
#include <SDL.h>
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>

#include "core/Log.h"

namespace gueepo {

	InputSystem* InputSystem::s_Instance = new SDL2Input();

	bool SDL2Input::Implementation_Initialize() {
		m_Controller = nullptr;
		m_State.Keyboard.CurrentState = SDL_GetKeyboardState(nullptr);

		m_Controller = SDL_GameControllerOpen(0);
		m_State.Controller.IsConnected = (m_Controller != nullptr);

		if (m_State.Controller.IsConnected) {
			LOG_INFO("[SDL2] Controller Connected!");
		}
		
		return true;
	}

	void SDL2Input::Implementation_Shutdown() { }

	void SDL2Input::Implementation_PrepareForUpdate() { }

	void SDL2Input::Implementation_Update() {
		int x = 0, y = 0;
		if (m_State.Mouse.IsRelative) { m_State.Mouse.MouseButtons = SDL_GetRelativeMouseState(&x, &y); }
		else { m_State.Mouse.MouseButtons = SDL_GetMouseState(&x, &y); }

		m_State.Mouse.MousePosition.x = static_cast<float>(x);
		m_State.Mouse.MousePosition.y = static_cast<float>(y);

		if (m_Controller != nullptr) {
			for (int i = 0; i < gueepo::ControllerCode::CONTROLLER_BUTTON_MAX; i++) {
				m_State.Controller.CurrentButtons[i] = SDL_GameControllerGetButton(m_Controller, SDL_GameControllerButton(i));
			}

			// Controller Triggers
			m_State.Controller.LeftTrigger = Filter1D(SDL_GameControllerGetAxis(m_Controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT));
			m_State.Controller.RightTrigger = Filter1D(SDL_GameControllerGetAxis(m_Controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT));

			// Controller Sticks
			x = SDL_GameControllerGetAxis(m_Controller,
				SDL_CONTROLLER_AXIS_LEFTX);
			y = -SDL_GameControllerGetAxis(m_Controller,
				SDL_CONTROLLER_AXIS_LEFTY);
			m_State.Controller.LeftStick = Filter2D(x, y);

			x = SDL_GameControllerGetAxis(m_Controller,
				SDL_CONTROLLER_AXIS_RIGHTX);
			y = -SDL_GameControllerGetAxis(m_Controller,
				SDL_CONTROLLER_AXIS_RIGHTY);
			m_State.Controller.RightStick = Filter2D(x, y);
		}
	}

	void SDL2Input::Implementation_SetRelativeMouseMode(bool Value) {
		SDL_bool ValueToSet = Value ? SDL_TRUE : SDL_FALSE;
		SDL_SetRelativeMouseMode(ValueToSet);
	}

}