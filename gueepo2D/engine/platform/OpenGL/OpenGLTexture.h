#pragma once
#include <stdint.h>
#include "core/renderer/Texture.h"

namespace gueepo {
	class OpenGLTexture : public Texture {
	public:

		OpenGLTexture(texture_data_t textureData);
		OpenGLTexture(uint32_t width, uint32_t height, bool bIsFont = false);
		~OpenGLTexture();

		uint32_t GetWidth() const override { return m_width; }
		uint32_t GetHeight() const override { return m_height; }
		uint32_t GetTextureID() const override { return m_textureID; }

		virtual void SetData(uint32_t* data, uint32_t size) override;
		virtual void SetData(unsigned char* data, uint32_t size) override;
		void Bind(uint32_t slot = 0) const override;
		bool IsLoaded() const override { return m_isLoaded; }

	private:
		friend class Texture;

		bool m_isLoaded;
		uint32_t m_textureID;
		int m_format;
		int m_width;
		int m_height;
	};
}