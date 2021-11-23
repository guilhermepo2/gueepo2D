#pragma once
#include <string>

namespace gueepo {
	class Shader {
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_ShaderProgramID;
		bool CompileShader(const char* shaderSource, unsigned int shaderType, unsigned int& outShader);
		bool IsShaderCompiled(unsigned int shader);
		bool IsShaderProgramValid();
	};
}