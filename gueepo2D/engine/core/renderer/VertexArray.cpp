#include "gueepo2Dpch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "platform/OpenGL/OpenGLVertexArray.h"

namespace gueepo {

	gueepo::VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case Renderer::API::OpenGL: {
			return new OpenGLVertexArray();
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