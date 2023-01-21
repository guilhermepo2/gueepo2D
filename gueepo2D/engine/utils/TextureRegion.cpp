#include "TextureRegion.h"
#include "core/Log.h"

namespace gueepo {
	TextureRegion::TextureRegion(Texture* texture, int x, int y, int w, int h) {
		g2dassert(texture != nullptr, "can't create a texture region with a null texture!");

		m_TextureRef = texture;

		uint32_t textureWidth = m_TextureRef->GetWidth();
		uint32_t textureHeight = m_TextureRef->GetHeight();

		m_texCoords.bottomLeft = math::vec2( (x / (float)textureWidth), (y / (float)textureHeight) );
		m_texCoords.topRight = math::vec2( ((x + w) / (float)textureWidth), ((y + h) / (float)textureHeight));
	}
}
