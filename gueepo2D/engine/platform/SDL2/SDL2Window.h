#pragma once
#include "core/Window.h"
#include "core/renderer/GraphicsContext.h"

struct SDL_Window;

namespace gueepo {
	class SDL2Window : public Window {
	public:
		SDL2Window(const WindowConfiguration& _config);
		virtual ~SDL2Window();
		void Update() override;
		void Swap() override;
		unsigned int GetWidth() const override { return m_Width; }
		unsigned int GetHeight() const override { return m_Height; }

		void SetEventCallback(const EventCallback& _callback) override { m_EventCallback = _callback; }
		void SetVSync(bool _enabled) override;
		bool IsVSyncEnabled() const override { return m_bIsVSyncEnabled; }
		void* GetNativeWindow() const override { return static_cast<void*>(m_Window); }

	private:
		void Initialize(const WindowConfiguration& _config);
		void Shutdown();

	private:
		unsigned int m_Width;
		unsigned int m_Height;
		std::string m_Title;
		bool m_bIsVSyncEnabled;
		EventCallback m_EventCallback;

		SDL_Window* m_Window;
		GraphicsContext* m_GraphicsContext;
	};
}