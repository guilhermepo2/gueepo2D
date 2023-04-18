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
		uint32_t GetTextureID() const override { return m_textureID; }

		virtual void SetData(uint32_t* data, uint32_t size) override;
		virtual void SetData(unsigned char* data, uint32_t size) override;
		void Bind(uint32_t slot = 0) const override;
		bool IsLoaded() const override { return m_isLoaded; }

	private:
		friend class Texture;

		bool m_isLoaded;
		uint32_t m_textureID;
		TEXTURE_DESCRIPTION m_textureDescription;
	};
}