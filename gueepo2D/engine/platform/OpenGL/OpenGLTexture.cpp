#include "gueepo2Dpch.h"
#include "core/Common.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include "utils/ImageUtils.h"

namespace gueepo {

	OpenGLTexture::OpenGLTexture(const std::string& path) {
		
		m_path = path;

		int channels = 0;
		unsigned char* imageData = g_LoadImage(path.c_str(), m_width, m_height, channels);
		m_format = channels == 4 ? GL_RGBA : GL_RGB;

		glGenTextures(1, &m_textureID);
		if (m_textureID == 0) {
			LOG_ERROR("error creating texture from file {0}", path);
			m_isLoaded = false;
			return;
		}

		m_isLoaded = true;
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		// #todo: this seems to be an outdated way of creating textures?
		glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, imageData);
		glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		g_FreeImage(imageData);
	}

	OpenGLTexture::~OpenGLTexture() {
		LOG_INFO("destroying texture: (id:{0})/(path:{1})", m_textureID, m_path);
		glDeleteTextures(1, &m_textureID);
	}

	void OpenGLTexture::Bind(uint32_t slot /*= 0*/) const {
		glBindTextureUnit(slot, m_textureID);
	}

}