#pragma once
#include "Event.h"

namespace gueepo {
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float _x, float _y) : m_MouseX(_x), m_MouseY(_y) {}
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		// #todo: override ToString();

		virtual int GetCategoryFlags() const override {
			return static_cast<int>(EventCategory::EC_Mouse);
		}

		EVENT_CLASS_TYPE(MouseMoved)
	private:
		float m_MouseX;
		float m_MouseY;
	};

	class MouseScrolledEvent : public Event {

		MouseScrolledEvent(float _x, float _y) : m_XOffset(_x), m_YOffset(_y) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		// #todo: override ToString();

		virtual int GetCategoryFlags() const override {
			return static_cast<int>(EventCategory::EC_Mouse);
		}

		EVENT_CLASS_TYPE(MouseScrolled)
	private:
		float m_XOffset;
		float m_YOffset;
	};

	class MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return m_Button; }

		virtual int GetCategoryFlags() const override {
			return
				static_cast<int>(EventCategory::EC_Mouse) |
				static_cast<int>(EventCategory::EC_Input) |
				static_cast<int>(EventCategory::EC_MouseButton);
		}

	protected:
		MouseButtonEvent(int _button) : m_Button(_button) {}
		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int _button) : MouseButtonEvent(_button) {}

		// #todo: override ToString();

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int _button) : MouseButtonEvent(_button) {}

		// #todo: override ToString();

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
