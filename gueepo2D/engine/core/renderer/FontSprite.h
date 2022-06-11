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
		Texture* texture = nullptr;
		int glyph = 0;
		math::vec2 size;
		math::vec2 bearing;
		float advance = 0.0f;
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
		const float& ascent() const { return m_ascent; }
		const float& descent() const { return m_descent; }
		const float& lineGap() const { return m_lineGap; }
		const float lineHeight() const { return ascent() - descent() + lineGap(); }
		const float kerning(int glyph1, int glyph2) const { return m_internalFontRef->GetKerning(glyph1, glyph2, m_scale); }

		void SetLineGap(float value) { m_lineGap = value; }

	private:
		Font* m_internalFontRef;
		float m_fontSize;
		float m_scale;

		float m_ascent;
		float m_descent;
		float m_lineGap;

		std::map<char, SpriteCharacter> m_Characters;
	};
}