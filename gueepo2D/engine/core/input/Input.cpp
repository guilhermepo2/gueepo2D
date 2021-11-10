#include "gueepo2Dpch.h"
#include "Input.h"
#include "core/Log.h"
#include <SDL.h>
#include <cstring>

namespace gueepo {
	// -------------------------------------------
	// Keyboard State
	// -------------------------------------------
	bool KeyboardState::GetKeyValue(Keycode key) const {
		return m_CurrentState[key] == 1;
	}

	EButtonState KeyboardState::GetKeyState(Keycode key) const {
		if (m_PreviousState[key] == 0) {
			if (m_CurrentState[key] == 0) { return None; }
			else { return Pressed; }
		}
		else {
			if (m_CurrentState[key] == 0) { return Released; }
			else { return Held; }
		}
	}

	bool KeyboardState::IsKeyDown(Keycode key) const { return (GetKeyState(key) == Pressed || GetKeyState(key) == Held); }
	bool KeyboardState::WasKeyPressedThisFrame(Keycode key) const { return (GetKeyState(key) == Pressed); }
	bool KeyboardState::WasKeyReleasedThisFrame(Keycode key) const { return (GetKeyState(key) == Released); }

	// -------------------------------------------
	// Mouse State
	// -------------------------------------------
	bool MouseState::GetButtonValue(Mousecode code) const {
		return (SDL_BUTTON(code) & m_MouseButtons == 1);
	}

	EButtonState MouseState::GetButtonState(Mousecode code) const {
		int mask = SDL_BUTTON(code);

		if (mask & m_MouseButtonsLastFrame == 0) {
			if (mask & m_MouseButtons == 0) { return None; }
			else { return Pressed; }
		}
		else {
			if (mask & m_MouseButtons == 0) { return Released; }
			else { return Held; }
		}
	}

	bool MouseState::IsMouseKeyDown(Mousecode code) const { return (GetButtonState(code) == Pressed || GetButtonState(code) == Held); }
	bool MouseState::WasMouseKeyPressedThisFrame(Mousecode code) const { return (GetButtonState(code) == Pressed); }
	bool MouseState::WasKMouseKeyReleasedThisFrame(Mousecode code) const { return (GetButtonState(code) == Released); }

	// -------------------------------------------
	// Input System
	// -------------------------------------------
	bool InputSystem::Initialize() {
		// Assign current state pointer
		m_State.Keyboard.m_CurrentState = SDL_GetKeyboardState(nullptr);
		memset(m_State.Keyboard.m_PreviousState, 0, SDL_NUM_SCANCODES);

		// Initializing Mouse
		m_State.Mouse.m_MouseButtons = 0;
		m_State.Mouse.m_MouseButtonsLastFrame = 0;

		LOG_INFO("[input] input system initialized");
		return true;
	}

	void InputSystem::Shutdown() { }

	void InputSystem::PrepareForUpdate() {
		memcpy(m_State.Keyboard.m_PreviousState, m_State.Keyboard.m_CurrentState, SDL_NUM_SCANCODES);

		// Mouse
		m_State.Mouse.m_MouseButtonsLastFrame = m_State.Mouse.m_MouseButtons;
		m_State.Mouse.m_IsRelative = false;
		m_State.Mouse.m_ScrollWheel = math::Vector2(0.0f, 0.0f);
	}

	void InputSystem::Update() {
		// Mouse
		int x = 0, y = 0;
		if (m_State.Mouse.m_IsRelative) { m_State.Mouse.m_MouseButtons = SDL_GetRelativeMouseState(&x, &y); }
		else { m_State.Mouse.m_MouseButtons = SDL_GetMouseState(&x, &y); }

		m_State.Mouse.m_MousePosition.x = static_cast<float>(x);
		m_State.Mouse.m_MousePosition.y = static_cast<float>(y);
	}

	void InputSystem::SetRelativeMouseMode(bool Value) {
		SDL_bool ValueToSet = Value ? SDL_TRUE : SDL_FALSE;
		SDL_SetRelativeMouseMode(ValueToSet);
		m_State.Mouse.m_IsRelative = Value;
	}
}