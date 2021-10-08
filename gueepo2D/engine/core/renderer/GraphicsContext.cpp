#include "gueepo2Dpch.h"
#include "GraphicsContext.h"
#include "RendererAPI.h"

#include "platform/OpenGL/OpenGLContext.h"

namespace gueepo {
	GraphicsContext* GraphicsContext::Create(void* window) {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
		case RendererAPI::API::Vulkan:
		case RendererAPI::API::DirectX:
		case RendererAPI::API::Metal:
			LOG_ERROR("API currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLContext(static_cast<SDL_Window*>(window));
			break;
		}

		return nullptr;
	}
}