#pragma once
#include "core/renderer/Shader.h"

namespace gueepo {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_ShaderProgramID;
		bool CompileShader(const char* shaderSource, unsigned int shaderType, unsigned int& outShader);
		bool IsShaderCompiled(unsigned int shader);
		bool IsShaderProgramValid();
	};
}