// ==========================================================================
// FontSprite.cpp
// 
// constructed from a Font file
// has all the information needed to draw text
// ==========================================================================

#include "gueepo2dpch.h"
#include "FontSprite.h"
#include "core/renderer/Texture.h"

namespace gueepo {

	FontSprite::FontSprite(Font* font, float size) {
		m_internalFontRef = font;
		m_fontSize = size;

		Rebuild();
	}

	void FontSprite::Rebuild() {
		if (m_internalFontRef == nullptr) {
			LOG_WARN("can't create a font sprite without a font reference!");
			return;
		}

		m_Characters.clear();

		m_scale = m_internalFontRef->GetScale(m_fontSize);

		for (int i = 0; i < 255; i++) {
			int glyph = m_internalFontRef->GetGlyphIndex(i);
			Character ch = m_internalFontRef->GetCharacter(glyph, m_scale);
			Texture* characterTexture = Texture::Create(ch.size.x, ch.size.y);

			unsigned char* characterBitmap = (unsigned char*)calloc(ch.size.x * ch.size.y, sizeof(unsigned char));
			m_internalFontRef->BlitCharacter(ch, ch.size.x, &characterBitmap);
			characterTexture->SetData(characterBitmap, ch.size.x * ch.size.y);

			SpriteCharacter character;
			character.texture = characterTexture;
			character.size = math::vec2(ch.size.x, ch.size.y);
			character.bearing = math::vec2(ch.offset.x, ch.offset.y);
			character.advance = ch.advance;
			
			free(characterBitmap);
			m_Characters.insert(std::pair<char, SpriteCharacter>(i, character));
		}
	}

}