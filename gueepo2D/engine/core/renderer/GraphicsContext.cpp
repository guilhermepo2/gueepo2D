#include "gueepo2Dpch.h"
#include "GraphicsContext.h"
#include "Renderer.h"

#include "platform/OpenGL/OpenGLContext.h"

namespace gueepo {
	GraphicsContext* GraphicsContext::Create(void* window) {
		switch (Renderer::GetAPI()) {
		case Renderer::API::None:
		case Renderer::API::Vulkan:
		case Renderer::API::DirectX:
		case Renderer::API::Metal:
			LOG_ERROR("API currently not supported!");
			break;
		case Renderer::API::OpenGL:
			return new OpenGLContext(static_cast<SDL_Window*>(window));
			break;
		}

		return nullptr;
	}
}