#include "PixelBuffer.h"

#include "core/renderer/Renderer.h"
#include "core/renderer/Texture.h"

gueepo::PixelBuffer::~PixelBuffer() {
	if (m_data != nullptr) {
		delete[] m_data;
	}
	m_data = nullptr;

	if (m_textureReference != nullptr) {
		delete m_textureReference;
	}
	m_textureReference = nullptr;
}

bool gueepo::PixelBuffer::SetColor(uint32_t x, uint32_t y, uint32_t color) {
	if (x < 0 || x > m_width || y < 0 || y > m_height) {
		return false;
	}

	m_data[(m_width * y) + x] = color;
	return true;
}


bool gueepo::PixelBuffer::SetColor(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	uint32_t color =
		((a & 0xFF) << 24) +
		((b & 0xFF) << 16) +
		((g & 0xFF) << 8) +
		((r & 0xFF));

	return SetColor(x, y, color);
}

bool gueepo::PixelBuffer::SetColor(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
	return SetColor(x, y, r, g, b, 255);
}

void gueepo::PixelBuffer::Render() {
	m_textureReference->SetData(m_data, m_width * m_height * sizeof(uint32_t));
	gueepo::Renderer::Draw(m_textureReference);
}


gueepo::PixelBuffer::PixelBuffer(uint32_t width, uint32_t height) {
	m_width = width;
	m_height = height;
	uint32_t dataSize = width * height;
	m_data = new uint32_t[dataSize];
	m_textureReference = Texture::Create(width, height);
}

gueepo::PixelBuffer* gueepo::PixelBuffer::Create(uint32_t width, uint32_t height) {
	return new PixelBuffer(width, height);
}
