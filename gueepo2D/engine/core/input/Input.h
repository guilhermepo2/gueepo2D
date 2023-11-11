#pragma once
#include "KeyboardCodes.h"
#include "MouseCodes.h"
#include "ControllerCodes.h"
#include "core/math/vec2.h"
#include "core/Common.h"
#include <stdint.h>

namespace gueepo {

	enum EButtonState {
		None = 0,
		Pressed,
		Released,
		Held
	};

	// -------------------------------------------
	// Keyboard State
	// -------------------------------------------
	class KeyboardState {
	public:
		friend class InputSystem;

		bool IsKeyDown(Keycode key) const;
		bool WasKeyPressedThisFrame(Keycode key) const;
		bool WasKeyReleasedThisFrame(Keycode key) const;

	private:
		bool GetKeyValue(Keycode key) const;
		EButtonState GetKeyState(Keycode key) const;

	public:
		const uint8_t* CurrentState;
		uint8_t PreviousState[NUM_KEYCODES];
	};

	// -------------------------------------------
	// Mouse State
	// -------------------------------------------
	class MouseState {
	public:
		const math::vec2 GetPosition() const { return MousePosition; }
		bool IsMouseKeyDown(Mousecode code) const;
		bool WasMouseKeyPressedThisFrame(Mousecode code) const;
		bool WasKMouseKeyReleasedThisFrame(Mousecode code) const;

	private:
		bool GetButtonValue(Mousecode code) const;
		EButtonState GetButtonState(Mousecode code) const;

	public:
		bool IsRelative = false;
		math::vec2 MousePosition;
		math::vec2 ScrollWheel;
		uint32_t MouseButtons = 0;
		uint32_t MouseButtonsLastFrame = 0;
	};

	class ControllerState {
	public:
		friend class InputSystem;

		bool GetButtonValue(gueepo::ControllerCode button) const;
		EButtonState GetButtonState(gueepo::ControllerCode button) const;
		bool IsButtonDown(gueepo::ControllerCode button) const;
		bool WasButtonPressedThisFrame(gueepo::ControllerCode button) const;
		bool WasButtonReleasedThisFrame(gueepo::ControllerCode button) const;

	public:
		uint8_t CurrentButtons[gueepo::ControllerCode::CONTROLLER_BUTTON_MAX];
		uint8_t PreviousButtons[gueepo::ControllerCode::CONTROLLER_BUTTON_MAX];
		float LeftTrigger;
		float RightTrigger;
		gueepo::math::vec2 LeftStick;
		gueepo::math::vec2 RightStick;
		bool IsConnected;
	};

	// -------------------------------------------
	// Input State
	// -------------------------------------------
	struct InputState {
		KeyboardState	Keyboard;
		MouseState		Mouse;
		ControllerState Controller;
	};

	// -------------------------------------------
	// Input System
	// -------------------------------------------
	class InputSystem {
	public:
		bool Initialize();
		void Shutdown();
		void PrepareForUpdate();
		void Update();
		void SetRelativeMouseMode(bool Value);
		const InputState& GetState() const { return m_State; }

	protected:
		virtual bool Implementation_Initialize() { return false; }
		virtual void Implementation_Shutdown() {}
		virtual void Implementation_PrepareForUpdate() {}
		virtual void Implementation_Update() {}
		virtual void Implementation_SetRelativeMouseMode(bool Value) { unreferenced(Value); }
		InputState m_State;

	protected:
		float Filter1D(int input);
		gueepo::math::vec2 Filter2D(int inputX, int inputY);

	public:
		static InputSystem* s_Instance;
	};
}