#pragma once
#include "core/renderer/Texture.h"

namespace gueepo {
	class OpenGLTexture : public Texture {
	public:

		OpenGLTexture(texture_data_t textureData);
		OpenGLTexture(uint32_t width, uint32_t height);
		~OpenGLTexture();

		uint32_t GetWidth() const { return m_width; }
		uint32_t GetHeight() const { return m_height; }
		uint32_t GetTextureID() const { return m_textureID; }

		virtual void SetData(uint32_t* data, uint32_t size) override;
		virtual void SetData(unsigned char* data, uint32_t size) override;
		void Bind(uint32_t slot = 0) const;
		bool IsLoaded() const { return m_isLoaded; }

	private:
		friend class Texture;

		bool m_isLoaded;
		uint32_t m_textureID;
		int m_format;
		int m_width;
		int m_height;
	};
}