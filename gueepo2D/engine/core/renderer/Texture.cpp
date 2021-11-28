#include "gueepo2Dpch.h"
#include "Texture.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "RendererAPI.h"

namespace gueepo {

	gueepo::Texture* Texture::Create(const std::string& path) {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::OpenGL: {
			return new OpenGLTexture(path);
		} break;
		case RendererAPI::API::DirectX:
		case RendererAPI::API::Metal:
		case RendererAPI::API::Vulkan:
		case RendererAPI::API::None:
		default:
			LOG_ERROR("API NOT SUPPORTED!");
			return nullptr;
			break;
		}
	}

}