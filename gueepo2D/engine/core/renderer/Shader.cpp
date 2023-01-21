#include "Shader.h"
#include "Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"

#include "core/Log.h"
#include "core/filesystem/File.h"
#include "core/Containers/hashed_string.h"
#include "core/Containers/string.h"

namespace gueepo {
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
		switch (Renderer::GetAPI()) {
		case Renderer::API::OpenGL: {
			return new OpenGLShader(vertexSource, fragmentSource);
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

	// ===============================================================================================
	// ===============================================================================================
	// Shader Library
	// ===============================================================================================
	// ===============================================================================================

	void ShaderLibrary::Add(const gueepo::hashed_string& name, Shader* shader) {
		m_Shaders[name] = shader;
	}

	Shader* ShaderLibrary::Load(const gueepo::hashed_string& name, const gueepo::string& vertex, const gueepo::string& fragment) {
		// todo: oof, maybe change Shader::CreateFromFile to use gueepo::string?
		Shader* shader = Shader::CreateFromFile(std::string(vertex), std::string(fragment));
		Add(name, shader);
		return shader;
	}

	gueepo::Shader* ShaderLibrary::Get(const gueepo::hashed_string& name) {
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(gueepo::hashed_string name) const {
		return m_Shaders.find(name) != m_Shaders.end();
	}

}