#include "gueepo2Dpch.h"
#include "Shader.h"
#include "RendererAPI.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "core/filesystem/File.h"

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

	gueepo::Shader* Shader::CreateFromFile(const std::string& vertexFile, const std::string& fragmentFile) {
		File* vertexShader = new File(vertexFile);
		File* fragmentShader = new File(fragmentFile);

		if (vertexShader->IsValid() && fragmentShader->IsValid()) {
			Shader* s = Shader::Create(vertexShader->GetStringContent(), fragmentShader->GetStringContent());
			delete vertexShader;
			delete fragmentShader;
			return s;
		}
		else {
			LOG_ERROR("couldn't create shader from files {0} and {1}", vertexFile, fragmentFile);
		}

		return nullptr;
	}

}