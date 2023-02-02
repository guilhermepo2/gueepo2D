#pragma once
#include <stdint.h>
// =====================================================================================
// PixelBuffer.h
// 
// A Pixel Buffer is an utility class that aims to facilitate creating and manipulating
// textures using your own code. Think of it as a canvas that you can choose the color
// for each single pixel
// =====================================================================================

namespace gueepo {

	class Texture;
	class SpriteBatcher;

	class PixelBuffer {
	public:
		~PixelBuffer();

		bool SetColor(uint32_t x, uint32_t y, uint32_t color);
		bool SetColor(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		bool SetColor(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
		void Render();

		static PixelBuffer* Create(uint32_t width, uint32_t height);
	protected:
		PixelBuffer(uint32_t width, uint32_t height);

		uint32_t m_width;
		uint32_t m_height;
		Texture* m_textureReference = nullptr;
		uint32_t* m_data = nullptr;
	};
}