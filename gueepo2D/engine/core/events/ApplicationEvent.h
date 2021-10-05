#pragma once
#include "Event.h"

namespace gueepo {

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int _width, unsigned int _height) : m_Width(_width), m_Height(_height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		virtual int GetCategoryFlags() const override {
			return static_cast<int>(EventCategory::EC_Application);
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent (" << m_Width << ", " << m_Height << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}
		
		virtual int GetCategoryFlags() const override {
			return static_cast<int>(EventCategory::EC_Application);
		}

		EVENT_CLASS_TYPE(WindowClose)
	};

	class AppTickEvent : public Event {
	public:
		AppTickEvent() {}
		
		virtual int GetCategoryFlags() const override {
			return static_cast<int>(EventCategory::EC_Application);
		}

		EVENT_CLASS_TYPE(AppTick)
	};

	class AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {}
		
		virtual int GetCategoryFlags() const override {
			return static_cast<int>(EventCategory::EC_Application);
		}

		EVENT_CLASS_TYPE(AppUpdate)
	};

	class AppRenderEvent : public Event {
	public:
		AppRenderEvent() {}
		
		virtual int GetCategoryFlags() const override { 
			return static_cast<int>(EventCategory::EC_Application); 
		}

		EVENT_CLASS_TYPE(AppRender)
	};

}
