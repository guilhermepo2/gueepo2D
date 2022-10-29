#include "gueepo2Dpch.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "platform/OpenGL/OpenGLIndexBuffer.h"

namespace gueepo {

	gueepo::IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case Renderer::API::OpenGL: {
			return new OpenGLIndexBuffer(indices, size);
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