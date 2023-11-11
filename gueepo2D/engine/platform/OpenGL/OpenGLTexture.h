#pragma once
#include <stdint.h>
#include "core/renderer/Texture.h"

namespace gueepo {
	class OpenGLTexture : public Texture {
	public:

		OpenGLTexture(TEXTURE_DESCRIPTION textureDescription);
		~OpenGLTexture();

		uint32_t GetWidth() const override { return m_textureDescription.width; }
		uint32_t GetHeight() const override { return m_textureDescription.height; }

		virtual void SetData(uint32_t* data, uint32_t size) override;
		virtual void SetData(unsigned char* data, uint32_t size) override;
		bool IsLoaded() const override { return m_isLoaded; }

	private:
		friend class Texture;
		bool m_isLoaded;
		TEXTURE_DESCRIPTION m_textureDescription;
	};
}