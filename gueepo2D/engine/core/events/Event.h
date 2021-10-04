#pragma once
#include "core/Common.h"
#include <string>

namespace gueepo {
	// #todo: have an event bus to buffer events and send them all at once instead of doing blocking events
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Have the bit thing here in case we need to filter events
	enum class EventCategory {
		None			= 0,
		EC_Application	= BIT(0),
		EC_Input		= BIT(1),
		EC_Keyboard		= BIT(2),
		EC_Mouse		= BIT(3),
		EC_MouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(t) static EventType GetStaticType() { return EventType::##t; } \
							virtual EventType GetEventType() const override { return GetStaticType(); } \
							virtual const char* GetName() const override { return #t; }
#define EVENT_CLASS_CATEGORY(c) virtual int GetCategoryFlags() const override { return EventCategory::##c; }

	class Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory c) {
			return GetCategoryFlags() & static_cast<int>(c);
		}

	protected:
		bool m_Handled = false;
	};

	// overriding << so we can print the event
	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}
