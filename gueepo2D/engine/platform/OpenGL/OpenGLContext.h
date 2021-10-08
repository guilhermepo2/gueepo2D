#pragma once
#include "core/renderer/GraphicsContext.h"

struct SDL_Window;

namespace gueepo {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(SDL_Window* _windowRef);
		virtual void Init() override;
		virtual void Swap() override;

	private:
		SDL_Window* m_WindowRef;
		void* m_GLContext;

	};
}