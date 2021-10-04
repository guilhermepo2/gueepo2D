#pragma once
#include "Event.h"
#include <functional>

namespace gueepo {
	class EventDispatcher {
		template<typename T>
		using EventFunction = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& e) : m_Event(e) {}

		template<typename T>
		bool Dispatch(EventFunction<T> f) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = f(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		// #todo: why not a pointer?
		Event& m_Event;
	};
}
