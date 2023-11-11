#pragma once
#include <stdint.h>
#include <string>

namespace gueepo {


	enum class TextureFilter { NONE, LINEAR, NEAREST };
	enum class TextureWrap	 { NONE, CLAMP, REPEAT };
	enum class TextureFormat { NONE, R8, RED, RGB, RGBA };

	struct TEXTURE_DESCRIPTION {
		unsigned char* data;
		int width;
		int height;
		int channels;

		TextureFilter minFilter;
		TextureFilter maxFilter;
		TextureWrap wrapS;
		TextureWrap wrapT;
		TextureFormat internalFormat;
		TextureFormat textureFormat;
	};

	class Texture {
	public:
		virtual ~Texture() {}
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		inline uint32_t GetTextureID() const { return m_textureID; }

		virtual void SetData(uint32_t* data, uint32_t size) = 0;
		virtual void SetData(unsigned char* data, uint32_t size) = 0;
		virtual bool IsLoaded() const = 0;

		static Texture* Create(const std::string& path);
		static Texture* Create(uint32_t width, uint32_t height);
        static Texture* CreateFontSprite(uint32_t width, uint32_t height);

	protected:
		uint32_t m_textureID;
		std::string m_path;

	};
}