#include <gueepo2Dpch.h>
#include "TextureRegion.h"

namespace gueepo {
	TextureRegion::TextureRegion(Texture* texture, int x, int y, int w, int h) {
		m_TextureRef = texture;

		uint32_t textureWidth = m_TextureRef->GetWidth();
		uint32_t textureHeight = m_TextureRef->GetHeight();

		m_texCoords.bottomLeft = math::vec2( (x / (float)textureWidth), (y / (float)textureHeight) );
		m_texCoords.topRight = math::vec2( ((x + w) / (float)textureWidth), ((y + h) / (float)textureHeight));
	}
}
