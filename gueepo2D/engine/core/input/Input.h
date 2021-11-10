#pragma once
#include "KeyboardCodes.h"
#include "MouseCodes.h"

// #todo: first step of this is making it work with SDL
// second step is moving all the SDL code to a platform specific file
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>

#include "core/math/Vector2.h"

namespace gueepo {

	namespace math {
		class Vector2;
	}

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
		bool GetKeyValue(Keycode key) const;
		EButtonState GetKeyState(Keycode key) const;

		bool IsKeyDown(Keycode key) const;
		bool WasKeyPressedThisFrame(Keycode key) const;
		bool WasKeyReleasedThisFrame(Keycode key) const;

	private:
		const Uint8* m_CurrentState;
		Uint8 m_PreviousState[NUM_SCANCODES];
	};

	// -------------------------------------------
	// Mouse State
	// -------------------------------------------
	class MouseState {
	public:
		friend class InputSystem;
		const math::Vector2 GetPosition() const { return m_MousePosition; }

		bool GetButtonValue(Mousecode code) const;
		EButtonState GetButtonState(Mousecode code) const;

		bool IsMouseKeyDown(Mousecode code) const;
		bool WasMouseKeyPressedThisFrame(Mousecode code) const;
		bool WasKMouseKeyReleasedThisFrame(Mousecode code) const;


	private:
		math::Vector2 m_MousePosition;
		math::Vector2 m_ScrollWheel;
		Uint32 m_MouseButtons;
		Uint32 m_MouseButtonsLastFrame;
		bool m_IsRelative;
	};

	// -------------------------------------------
	// Input State
	// -------------------------------------------
	struct InputState {
		KeyboardState	Keyboard;
		MouseState		Mouse;
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

	private:
		InputState m_State;
	};
}