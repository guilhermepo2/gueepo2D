// ==========================================================================
// FontSprite.h
// 
// constructed from a Font file
// has all the information needed to draw text
// ==========================================================================

#pragma once
#include "core/math/vec2.h"
#include "core/filesystem/Font.h"
#include <map>

namespace gueepo {

	class Font;
	class Texture;

	struct SpriteCharacter {
		Texture* texture;
		int glyph;
		math::vec2 size;
		math::vec2 bearing;
		unsigned int advance;
	};

	struct CharacterRange {
		uint32_t from;
		uint32_t to;

		CharacterRange(uint32_t from, uint32_t to);

		static const CharacterRange ASCII;
	};


	class FontSprite {
	public:
		FontSprite(Font* font, float size);

		void Rebuild();
		SpriteCharacter GetSpriteCharacter(char c) { return m_Characters[c]; }

		const float& scale() const { return m_scale; }
		const int& ascent() const { return m_internalFontRef->GetAscent() * m_scale; }
		const int& descent() const { return m_internalFontRef->GetDescent() * m_scale; }
		const float& kerning(int glyph1, int glyph2) const { return m_internalFontRef->GetKerning(glyph1, glyph2, m_scale); }

	private:
		Font* m_internalFontRef;
		float m_fontSize;
		float m_scale;

		std::map<char, SpriteCharacter> m_Characters;
	};
}