#pragma once
#include <string>
#include <functional>
#include "core/Common.h"
#include "core/events/Event.h"

namespace gueepo {
	struct WindowConfiguration {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowConfiguration(const std::string& _Title, unsigned int _Width, unsigned int _Height)
			: Title(_Title), Width(_Width), Height(_Height) {}
	};

	class Window {
	public:
		using EventCallback = std::function<void(Event&)>;
		virtual ~Window() = default;
		virtual void Update() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallback& _callback) = 0;
		virtual void SetVSync(bool _enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;
		virtual void* GetNativeWindow() const = 0;

		static Window* CreateNewWindow(const WindowConfiguration& _props);
	};
}