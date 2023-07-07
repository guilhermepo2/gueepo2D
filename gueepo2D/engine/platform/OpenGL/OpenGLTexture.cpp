#include "core/Common.h"
#include "OpenGLTexture.h"
#include "core/Log.h"
#include "core/math/math.h"
#include <glad/glad.h>

namespace gueepo {


	static int GetOpenGLFilter(TextureFilter filter) {
		switch (filter) {
		case TextureFilter::NONE:
			return GL_NONE;
		case TextureFilter::LINEAR:
			return GL_LINEAR;
		case TextureFilter::NEAREST:
			return GL_NEAREST;
		default:
			return GL_NONE;
		}

		return GL_NONE;
	}

	static int GetOpenGLWrap(TextureWrap wrap) {
		switch (wrap) {
		case TextureWrap::NONE:
			return GL_NONE;
		case TextureWrap::CLAMP:
			return GL_CLAMP_TO_EDGE;
		case TextureWrap::REPEAT:
			return GL_REPEAT;
		default:
			return GL_NONE;
		}

		return GL_NONE;
	}

	static int GetOpenGLFormat(TextureFormat format) {
		switch (format) {
		case TextureFormat::NONE:
			return GL_NONE;
		case TextureFormat::R8:
			return GL_R8;
		case TextureFormat::RED:
			return GL_RED;
		case TextureFormat::RGB:
			return GL_RGB;
		case TextureFormat::RGBA:
			return GL_RGBA;
		default:
			return GL_NONE;
		}

		return GL_NONE;
	}

	OpenGLTexture::OpenGLTexture(TEXTURE_DESCRIPTION textureDescription) {
		m_textureID = 0;
		m_textureDescription = textureDescription;

		glGenTextures(1, &m_textureID);

		if (m_textureID == 0) {
			LOG_ERROR("error creating texture from file {0}", m_path);
			m_isLoaded = false;
			return;
		}

		m_isLoaded = true;
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetOpenGLFilter(textureDescription.minFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetOpenGLFilter(textureDescription.maxFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetOpenGLWrap(textureDescription.wrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetOpenGLWrap(textureDescription.wrapT));
		glTexImage2D(
			GL_TEXTURE_2D,
			0, 
			GetOpenGLFormat(textureDescription.internalFormat),
			textureDescription.width,
			textureDescription.height,
			0,
			GetOpenGLFormat(textureDescription.textureFormat),
			GL_UNSIGNED_BYTE,
			m_textureDescription.data
		);
	}

	OpenGLTexture::~OpenGLTexture() {
		LOG_INFO("destroying texture: (id:{0})/(path:{1})", m_textureID, m_path);
		glDeleteTextures(1, &m_textureID);
	}

	void OpenGLTexture::SetData(uint32_t* data, uint32_t size) {
		g2dassert(size == GetWidth() * GetHeight() * sizeof(uint32_t), "data must be the entire texture!");
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexSubImage2D(
			GL_TEXTURE_2D, 
			0, 
			0, 
			0,
			m_textureDescription.width, 
			m_textureDescription.height, 
			GetOpenGLFormat(m_textureDescription.textureFormat), 
			GL_UNSIGNED_BYTE, 
			data
		);
	}

	void OpenGLTexture::SetData(unsigned char* data, uint32_t size) {
		g2dassert(size == GetWidth() * GetHeight() * sizeof(unsigned char), "data must be the entire texture! size: {0}/width:{1}/height:{2}", size, GetWidth(), GetHeight());
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexSubImage2D(
			GL_TEXTURE_2D,
			0,
			0,
			0,
			m_textureDescription.width,
			m_textureDescription.height,
			GetOpenGLFormat(m_textureDescription.textureFormat),
			GL_UNSIGNED_BYTE,
			data
		);
	}

}