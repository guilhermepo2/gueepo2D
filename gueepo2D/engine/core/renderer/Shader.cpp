#include "gueepo2Dpch.h"
#include "Shader.h"

// #todo: THIS IS TEMPORARY!
#include <SDL.h>
#include <glad/glad.h>

namespace gueepo {

	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) {
		unsigned int vertexShader, fragmentShader;
		CompileShader(vertexSource.c_str(), GL_VERTEX_SHADER, vertexShader);
		CompileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER, fragmentShader);
		
		m_ShaderProgramID = glCreateProgram();
		glAttachShader(m_ShaderProgramID, vertexShader);
		glAttachShader(m_ShaderProgramID, fragmentShader);
		glLinkProgram(m_ShaderProgramID);

		IsShaderProgramValid();

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	Shader::~Shader() {
		glDeleteProgram(m_ShaderProgramID);
	}

	void Shader::Bind() const {
		glUseProgram(m_ShaderProgramID);
	}

	void Shader::Unbind() const {
		glUseProgram(0);
	}

	bool Shader::CompileShader(const char* shaderSource, unsigned int shaderType, unsigned int& outShader) {
		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &shaderSource, nullptr);
		glCompileShader(outShader);

		return IsShaderCompiled(outShader);
	}

	bool Shader::IsShaderCompiled(unsigned int shader) {
		int success;
		char infoLog[512];
		memset(infoLog, 0, 512);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(shader, 511, nullptr, infoLog);
			LOG_ERROR("FAILED TO COMPILE SHADER: {0}\n", infoLog);
			return false;
		}

		return true;
	}

	bool Shader::IsShaderProgramValid() {
		int success;
		char infoLog[512];
		memset(infoLog, 0, 512);

		glGetProgramiv(m_ShaderProgramID, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(m_ShaderProgramID, 511, nullptr, infoLog);
			LOG_ERROR("ERROR LINKING SHADER PROGRAM: {0}\n", infoLog);
			return false;
		}

		return true;
	}

}