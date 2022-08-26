#include "gueepo2Dpch.h"
#include "VertexArray.h"
#include "RendererAPI.h"

#include "platform/OpenGL/OpenGLVertexArray.h"

namespace gueepo {

	gueepo::VertexArray* VertexArray::Create() {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::OpenGL: {
			return new OpenGLVertexArray();
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