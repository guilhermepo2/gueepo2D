#include "gueepo2Dpch.h"
#include "core/Common.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>

namespace gueepo {
	OpenGLTexture::OpenGLTexture(texture_data_t textureData) {
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
		glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, textureData.texture_data);
		glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	OpenGLTexture::~OpenGLTexture() {
		LOG_INFO("destroying texture: (id:{0})/(path:{1})", m_textureID, m_path);
		glDeleteTextures(1, &m_textureID);
	}

	void OpenGLTexture::Bind(uint32_t slot /*= 0*/) const {
		glBindTextureUnit(slot, m_textureID);
	}

}