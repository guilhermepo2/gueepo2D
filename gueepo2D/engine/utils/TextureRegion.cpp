#include "TextureRegion.h"
#include "core/Log.h"

namespace gueepo {
	TextureRegion::TextureRegion(Texture* texture, int x, int y, int w, int h, TEXTURE_ORIGIN origin) {
		g2dassert(texture != nullptr, "can't create a texture region with a null texture!");

		m_TextureRef = texture;
        m_width = w;
        m_height = h;

		uint32_t textureWidth = m_TextureRef->GetWidth();
		uint32_t textureHeight = m_TextureRef->GetHeight();
		float fTextureWidth = static_cast<float>(textureWidth);
		float fTextureHeight = static_cast<float>(textureHeight);

		// If ORIGIN is BOTTOM_LEFT (default)
		// Then the Y goes from y to y+h
		// But it ORIGIN is TOP_LEFT (the more intuitive)
		// Then the Y goes from ( (tex_h - h ) - y) to ( start + h )
		int startY = y;
		if (origin == TOP_LEFT) {
			startY = (textureHeight - h) - y;
		}
		int endY = startY + h;

		m_texCoords.bottomLeft = math::vec2( (x / fTextureWidth), (startY / fTextureHeight) );
		m_texCoords.topRight = math::vec2( ((x + w) / fTextureWidth), (endY / fTextureHeight));
	}
}
