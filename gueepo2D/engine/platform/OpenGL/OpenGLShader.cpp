#include "gueepo2Dpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include "core/math/Matrix4.h"

namespace gueepo {

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource) {
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

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_ShaderProgramID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_ShaderProgramID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::SetMat4(const std::string& name, math::Matrix4 mat) const {
		glUniformMatrix4fv(
			glGetUniformLocation(m_ShaderProgramID, name.c_str()),
			1,
			GL_FALSE,
			mat.GetValueData()
		);
	}

	bool OpenGLShader::CompileShader(const char* shaderSource, unsigned int shaderType, unsigned int& outShader) {
		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &shaderSource, nullptr);
		glCompileShader(outShader);

		return IsShaderCompiled(outShader);
	}

	bool OpenGLShader::IsShaderCompiled(unsigned int shader) {
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

	bool OpenGLShader::IsShaderProgramValid() {
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