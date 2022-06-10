// ==========================================================================
// FontSprite.cpp
// 
// constructed from a Font file
// has all the information needed to draw text
// ==========================================================================

#include "gueepo2dpch.h"
#include "FontSprite.h"
#include "core/renderer/Texture.h"
#include "core/renderer/Renderer.h"

namespace gueepo {

	CharacterRange::CharacterRange(uint32_t from, uint32_t to) : from(from), to(to) {}
	const CharacterRange CharacterRange::ASCII = CharacterRange(32, 128);

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

		Renderer::SetUnpackAlignment(1);

		for (int i = CharacterRange::ASCII.from; i < CharacterRange::ASCII.to; i++) {
			int glyph = m_internalFontRef->GetGlyphIndex(i);
			Character ch = m_internalFontRef->GetCharacter(glyph, m_scale);
			Texture* characterTexture = Texture::Create(ch.size.x, ch.size.y);

			unsigned char* characterBitmap = (unsigned char*)calloc(ch.size.x * ch.size.y, sizeof(unsigned char));
			m_internalFontRef->BlitCharacter(ch, ch.size.x, &characterBitmap);
			characterTexture->SetData(characterBitmap, ch.size.x * ch.size.y);

			SpriteCharacter character;
			character.texture = characterTexture;
			character.glyph = glyph;
			character.size = math::vec2(ch.size.x, ch.size.y);
			character.bearing = math::vec2(ch.offset.x, ch.offset.y) * m_scale;
			character.advance = ch.advance;
			
			free(characterBitmap);
			m_Characters.insert(std::pair<char, SpriteCharacter>(i, character));
		}

		Renderer::SetUnpackAlignment(4);
	}

}