#pragma once
#include "Event.h"

namespace gueepo {
	
	class KeyEvent : public Event {
	public:

		inline int GetKeyCode() const { return m_KeyCode; }

		virtual int GetCategoryFlags() const override {
			return
				static_cast<int>(EventCategory::EC_Input) | 
				static_cast<int>(EventCategory::EC_Keyboard);
		}
	protected:
		KeyEvent(int _keyCode) : m_KeyCode(_keyCode) {}
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int _keyCode, int _repeatCount) : KeyEvent(_keyCode), m_RepeatCount(_repeatCount) {}
		inline int GetRepeatCount() const { return m_RepeatCount; }
		
		// #todo: override ToString()

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
		KeyReleasedEvent(int _keyCode) : KeyEvent(_keyCode) {}

		// #todo: override ToString()

		EVENT_CLASS_TYPE(KeyReleased)
	};

}
