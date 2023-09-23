#include "Input.h"
#include "core/Log.h"
#include <cstring>

namespace gueepo {

	// -------------------------------------------
	// Keyboard State
	// -------------------------------------------
	bool KeyboardState::GetKeyValue(Keycode key) const {
		return CurrentState[key] == 1;
	}

	EButtonState KeyboardState::GetKeyState(Keycode key) const {
		if (PreviousState[key] == 0) {
			if (CurrentState[key] == 0) { return None; }
			else { return Pressed; }
		}
		else {
			if (CurrentState[key] == 0) { return Released; }
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
		return ( (MOUSE_BUTTON(code) & MouseButtons) == 1);
	}

	EButtonState MouseState::GetButtonState(Mousecode code) const {
		int mask = MOUSE_BUTTON(code);

		if ( (mask & MouseButtonsLastFrame) == 0) {
			if ( (mask & MouseButtons) == 0) { return None; }
			else { return Pressed; }
		}
		else {
			if ((mask & MouseButtons) == 0) { return Released; }
			else { return Held; }
		}
	}

	bool MouseState::IsMouseKeyDown(Mousecode code) const { return (GetButtonState(code) == Pressed || GetButtonState(code) == Held); }
	bool MouseState::WasMouseKeyPressedThisFrame(Mousecode code) const { return (GetButtonState(code) == Pressed); }
	bool MouseState::WasKMouseKeyReleasedThisFrame(Mousecode code) const { return (GetButtonState(code) == Released); }

	// -------------------------------------------
	// Controller State
	// -------------------------------------------
	bool ControllerState::GetButtonValue(gueepo::ControllerCode button) const {
		return CurrentButtons[button] == 1;
	}

	gueepo::EButtonState ControllerState::GetButtonState(gueepo::ControllerCode button) const {
		if (PreviousButtons[button] == 0) {
			if (CurrentButtons[button] == 0) { return None; }
			else { return Pressed; }
		}
		else {
			if (CurrentButtons[button] == 0) { return Released; }
			else { return Held; }
		}
	}

	bool ControllerState::IsButtonDown(gueepo::ControllerCode button) const {
		return GetButtonState(button) == Pressed || GetButtonState(button) == Held;
	}

	bool ControllerState::WasButtonPressedThisFrame(gueepo::ControllerCode button) const {
		return GetButtonState(button) == Pressed;
	}

	bool ControllerState::WasButtonReleasedThisFrame(gueepo::ControllerCode button) const {
		return GetButtonState(button) == Released;
	}

	// -------------------------------------------
	// Input System
	// -------------------------------------------
	bool InputSystem::Initialize() { 
		memset(m_State.Keyboard.PreviousState, 0, NUM_KEYCODES);
		m_State.Mouse.MouseButtons = 0;
		m_State.Mouse.MouseButtonsLastFrame = 0;

		memset(m_State.Controller.PreviousButtons, 0, gueepo::ControllerCode::CONTROLLER_BUTTON_MAX);
		memset(m_State.Controller.CurrentButtons, 0, gueepo::ControllerCode::CONTROLLER_BUTTON_MAX);

		s_Instance->Implementation_Initialize();
		LOG_INFO("[input] input system initialized");
		return true;
	}

	void InputSystem::Shutdown() {  
		s_Instance->Implementation_Shutdown();
	}
	
	void InputSystem::PrepareForUpdate() { 
		memcpy(m_State.Keyboard.PreviousState, m_State.Keyboard.CurrentState, NUM_KEYCODES);
		memcpy(m_State.Controller.PreviousButtons, m_State.Controller.CurrentButtons, gueepo::ControllerCode::CONTROLLER_BUTTON_MAX);

		m_State.Mouse.MouseButtonsLastFrame = m_State.Mouse.MouseButtons;
		m_State.Mouse.IsRelative = false;
		m_State.Mouse.ScrollWheel = math::vec2(0.0f, 0.0f);

		s_Instance->Implementation_PrepareForUpdate();
	}

	void InputSystem::Update() { 
		s_Instance->Implementation_Update(); 
	}

	void InputSystem::SetRelativeMouseMode(bool Value) { 
		s_Instance->Implementation_SetRelativeMouseMode(Value);
		m_State.Mouse.IsRelative = Value;
	}
}