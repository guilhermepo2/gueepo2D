#include "Texture.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "Renderer.h"
#include "utils/ImageUtils.h"
#include "core/Log.h"

namespace gueepo {

	gueepo::Texture* Texture::Create(const std::string& path) {
		TEXTURE_DESCRIPTION desc;
		desc.data = g_LoadImage(path.c_str(), desc.width, desc.height, desc.channels);
		desc.minFilter = TextureFilter::NEAREST;
		desc.maxFilter = TextureFilter::NEAREST;
		desc.wrapS = TextureWrap::CLAMP;
		desc.wrapT = TextureWrap::CLAMP;
		desc.internalFormat = desc.channels == 4 ? TextureFormat::RGBA : TextureFormat::RGB;
		desc.textureFormat = desc.internalFormat;


		switch (Renderer::GetAPI()) {
		case Renderer::API::OpenGL: {
			OpenGLTexture* tex = new OpenGLTexture(desc);
			tex->m_path = path;
			g_FreeImage(desc.data);
			return tex;
		} break;
		case Renderer::API::DirectX:
		case Renderer::API::Metal:
		case Renderer::API::Vulkan:
		case Renderer::API::None:
		default:
			LOG_ERROR("API NOT SUPPORTED!");
			return nullptr;
			break;
		}
	}


	gueepo::Texture* Texture::Create(uint32_t width, uint32_t height) {
		TEXTURE_DESCRIPTION desc;
		desc.data = nullptr;
		desc.width = width;
		desc.height = height;
		desc.minFilter = TextureFilter::NEAREST;
		desc.maxFilter = TextureFilter::NEAREST;
		desc.wrapS = TextureWrap::CLAMP;
		desc.wrapT = TextureWrap::CLAMP;
		desc.internalFormat = TextureFormat::RGBA;
		desc.textureFormat = TextureFormat::RGBA;

		switch (Renderer::GetAPI()) {
		case Renderer::API::OpenGL: {
			return new OpenGLTexture(desc);
		} break;
		case Renderer::API::DirectX:
		case Renderer::API::Metal:
		case Renderer::API::Vulkan:
		case Renderer::API::None:
		default:
			LOG_ERROR("API NOT SUPPORTED!");
			return nullptr;
			break;
		}
	}

	gueepo::Texture* Texture::CreateFontSprite(uint32_t width, uint32_t height) {

		TEXTURE_DESCRIPTION desc;
		desc.data = nullptr;
		desc.width = width;
		desc.height = height;
		desc.minFilter = TextureFilter::NEAREST;
		desc.maxFilter = TextureFilter::NEAREST;
		desc.wrapS = TextureWrap::CLAMP;
		desc.wrapT = TextureWrap::CLAMP;
		desc.internalFormat = TextureFormat::R8;
		desc.textureFormat = TextureFormat::RED;

		switch (Renderer::GetAPI()) {
		case Renderer::API::OpenGL: {
			return new OpenGLTexture(desc);
		} break;
		case Renderer::API::DirectX:
		case Renderer::API::Metal:
		case Renderer::API::Vulkan:
		case Renderer::API::None:
		default:
			LOG_ERROR("API NOT SUPPORTED!");
			return nullptr;
			break;
		}
	}
}