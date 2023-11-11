
#include "OpenGLMaterial.h"

#include "core/Log.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include <glad/glad.h>

#define ASSERT_MATERIAL() g2dassert(m_Shader != nullptr, "setting material without a shader?")
#define ASSERT_MATERIAL_BIND() g2dassert(m_Shader != nullptr, "binding material without a shader?")

namespace gueepo {
    
	OpenGLMaterial::~OpenGLMaterial() {
		if (m_Textures != nullptr) {
			delete[] m_Textures;
		}
	}

	void OpenGLMaterial::Set(const gueepo::string& name, math::mat4 mat) const {
		ASSERT_MATERIAL();

		uint32_t shaderProgramID = m_Shader->GetShaderProgramID();
		glUniformMatrix4fv(
			glGetUniformLocation(shaderProgramID, name.c_str()),
			1,
			GL_FALSE,
			mat.GetValueData()
		);
	}

	void OpenGLMaterial::Set(const gueepo::string& name, float x, float y, float z, float w) const {
		ASSERT_MATERIAL();

		uint32_t shaderProgramID = m_Shader->GetShaderProgramID();
		glUniform4f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y, z, w);
	}

	void OpenGLMaterial::Set(Texture* tex) const {
		ASSERT_MATERIAL();
		g2dassert(tex != nullptr, "trying to bind null texture?");

		uint32_t texID = tex->GetTextureID();
		glBindTexture(GL_TEXTURE_2D, texID);
	}

	void OpenGLMaterial::Set(Texture* tex, int index) const {
		ASSERT_MATERIAL();
		g2dassert(tex != nullptr, "trying to bind null texture?");

		uint32_t texID = tex->GetTextureID();
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, texID);
	}

	void OpenGLMaterial::SetupTextureSamplerArray(const gueepo::string& name, int size)  {
		ASSERT_MATERIAL();

		uint32_t ShaderProgramID = m_Shader->GetShaderProgramID();
		glUseProgram(ShaderProgramID);
		auto loc = glGetUniformLocation(ShaderProgramID, name.c_str());

		int* samplers = new int[size];
		
		m_Textures = new Texture * [size];
		m_maxTextures = size;

		for (int i = 0; i < size; i++) {
			samplers[i] = i;
			m_Textures[i] = nullptr;
		}

		glUniform1iv(loc, size, samplers);

		delete[] samplers;
	}

	void OpenGLMaterial::Bind() const {
		ASSERT_MATERIAL_BIND();

		for (int i = 0; i < m_maxTextures; i++) {
			if (m_Textures[i] == nullptr) {
				continue;
			}

			Set(m_Textures[i], i);
		}
		
		uint32_t ShaderProgramID = m_Shader->GetShaderProgramID();
		glUseProgram(ShaderProgramID);
	}

	void OpenGLMaterial::Unbind() const {
		glUseProgram(0);
	}

}