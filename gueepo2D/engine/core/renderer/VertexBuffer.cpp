#include "gueepo2Dpch.h"
#include "VertexBuffer.h"
#include "RendererAPI.h"
#include "platform/OpenGL/OpenGLVertexBuffer.h"

namespace gueepo {

	gueepo::VertexBuffer* VertexBuffer::Create(uint32_t size) {
		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::OpenGL: {
				return new OpenGLVertexBuffer(size);
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

	gueepo::VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::OpenGL: {
			return new OpenGLVertexBuffer(vertices, size);
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