#include "gueepo2Dpch.h"
#include "core/Common.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include "core/Log.h"
#include "core/math/math.h"

namespace gueepo {
	OpenGLTexture::OpenGLTexture(texture_data_t textureData) {
		LOG_INFO("creating opengl texture");
		m_textureID = 0; // shut up MSVC
		m_format = textureData.channels == 4 ? GL_RGBA : GL_RGB;
		m_width = textureData.width;
		m_height = textureData.height;

		if (textureData.texture_data == nullptr) {
			LOG_ERROR("trying to create texture with null data! path: {0}", m_path);
			m_isLoaded = false;
			return;
		}

		glGenTextures(1, &m_textureID);

		if (m_textureID == 0) {
			LOG_ERROR("error creating texture from file {0}", m_path);
			m_isLoaded = false;
			return;
		}

		m_isLoaded = true;

		glBindTexture(GL_TEXTURE_2D, m_textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, textureData.texture_data);
	}

	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height) {
		m_isLoaded = false;
		m_textureID = 0;
		m_width = width;
		m_height = height;
		m_format = GL_RGBA;

		glGenTextures(1, &m_textureID);

		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	OpenGLTexture::~OpenGLTexture() {
		LOG_INFO("destroying texture: (id:{0})/(path:{1})", m_textureID, m_path);
		glDeleteTextures(1, &m_textureID);
	}

	void OpenGLTexture::SetData(uint32_t* data, uint32_t size) {
		g2dassert(size == m_width * m_height * sizeof(uint32_t), "data must be the entire texture!");
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, m_format, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture::SetData(unsigned char* data, uint32_t size) {
		g2dassert(size == m_width * m_height * sizeof(unsigned char), "data must be the entire texture!");
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RED, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture::Bind(uint32_t slot /*= 0*/) const {
		// glBindTextureUnit(slot, m_textureID);

		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

}