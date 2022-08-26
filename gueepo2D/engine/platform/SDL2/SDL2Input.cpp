#include "gueepo2Dpch.h"
#include "SDL2Input.h"
#include <SDL.h>
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
namespace gueepo {

	InputSystem* InputSystem::s_Instance = new SDL2Input();

	bool SDL2Input::Implementation_Initialize() {
		m_State.Keyboard.CurrentState = SDL_GetKeyboardState(nullptr);
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
	}

	void SDL2Input::Implementation_SetRelativeMouseMode(bool Value) {
		SDL_bool ValueToSet = Value ? SDL_TRUE : SDL_FALSE;
		SDL_SetRelativeMouseMode(ValueToSet);
	}

}