#include "gueepo2Dpch.h"
#include "VertexBuffer.h"
#include "Renderer.h"
#include "platform/OpenGL/OpenGLVertexBuffer.h"

namespace gueepo {

	gueepo::VertexBuffer* VertexBuffer::Create(uint32_t size) {
		switch (Renderer::GetAPI()) {
			case Renderer::API::OpenGL: {
				return new OpenGLVertexBuffer(size);
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

	gueepo::VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case Renderer::API::OpenGL: {
			return new OpenGLVertexBuffer(vertices, size);
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