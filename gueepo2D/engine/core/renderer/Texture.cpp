#include "gueepo2Dpch.h"
#include "Texture.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "RendererAPI.h"
#include "utils/ImageUtils.h"

namespace gueepo {

	gueepo::Texture* Texture::Create(const std::string& path) {
		// loading texture here and sending it to the platform specific texture.
		texture_data_t textureData = LoadTexture(path);

		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::OpenGL: {
			OpenGLTexture* tex = new OpenGLTexture(textureData);
			tex->m_path = path;
			// I don't like having this here... ideally this should be outside the switch-case
			g_FreeImage(textureData.texture_data);
			return tex;
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


	gueepo::Texture* Texture::Create(uint32_t width, uint32_t height) {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::OpenGL: {
			return new OpenGLTexture(width, height);
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

	gueepo::texture_data_t Texture::LoadTexture(const std::string& path) {
		texture_data_t tex;
		tex.texture_data = g_LoadImage(path.c_str(), tex.width, tex.height, tex.channels);
		return tex;
	}

}