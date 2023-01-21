// ==========================================================================
// Font.h
// 
// internal representation of a font file
// ==========================================================================

#pragma once
#include "core/Containers/string.h"
#include "core/math/vec2.h"
#include <string>

namespace gueepo {
	struct Character {
		int glyph = 0;
		math::vec2 size;
		math::vec2 offset;
		float advance = 0; // how much to move horizontally
		float scale = 0;

		bool has_glyph = false;
	};

	class Font {

	public:
		Font();
		~Font();

		static Font* CreateNewFont(const std::string& path);

		const gueepo::string& GetFamilyName() const { return m_familyName; }
		const gueepo::string& GetStyleName() const { return m_styleName; }
		const int& GetAscent() const { return m_ascent; }
		const int& GetDescent() const { return m_descent; }
		const int& GetLineGap() const { return m_lineGap; }
		const int GetFontHeight() const { return m_ascent - m_descent; }
		const int GetFontLineHeight() const { return m_descent - m_descent + m_lineGap; }
		
		float GetScale(float size) const;
		float GetKerning(int glyph1, int glyph2, float scale) const;

		Character GetCharacter(int glyph, float scale) const;
		int GetGlyphIndex(uint32_t codepoint) const;
		bool BlitCharacter(const Character& ch, int outStride, unsigned char** pixels) const;

	private:
		void* m_font;
		unsigned char* m_internalBuffer;
		gueepo::string m_familyName;
		gueepo::string m_styleName;

		// ascent is the coordinate above the baseline the font extends;
		int m_ascent = 0;
		// descent is the coordinate below the baseline the font extends (i.e. it is typically negative)
		int m_descent = 0;
		// lineGap is the spacing between one row's descent and the next row's ascent...
		// so you should advance the vertical position by "*ascent - *descent + *lineGap"
		//   these are expressed in unscaled coordinates, so you must multiply by
		//   the scale factor for a given size
		int m_lineGap = 0;
	};
}