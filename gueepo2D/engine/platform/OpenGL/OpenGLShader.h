#pragma once
#include "core/renderer/Shader.h"

namespace gueepo {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

	private:
		bool CompileShader(const char* shaderSource, unsigned int shaderType, unsigned int& outShader);
		bool IsShaderCompiled(unsigned int shader);
		bool IsShaderProgramValid();
	};
}