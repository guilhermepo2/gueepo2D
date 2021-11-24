#include "gueepo2Dpch.h"
#include "Shader.h"
#include "RendererAPI.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace gueepo {
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::OpenGL: {
			return new OpenGLShader(vertexSource, fragmentSource);
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