#include "gueepo2Dpch.h"
#include "IndexBuffer.h"
#include "RendererAPI.h"
#include "platform/OpenGL/OpenGLIndexBuffer.h"

namespace gueepo {

	gueepo::IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::OpenGL: {
			return new OpenGLIndexBuffer(indices, size);
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