#pragma once
#include <string>

namespace gueepo {
	struct Character {
		int glyph = 0;
		int width = 0;
		int height = 0;
		float advance = 0; // how much to move horizontally
		float offset_x = 0;
		float offset_y = 0;
		float scale = 0;

		bool has_glyph = false;
	};

	class Font {

	public:
		

		Font();
		~Font();

		static Font* CreateFont(const std::string& path);


		const std::string& GetFamilyName() const { return m_familyName; }
		const std::string& GetStyleName() const { return m_styleName; }
		const int& GetAscent() const { return m_ascent; }
		const int& GetDescent() const { return m_descent; }
		const int& GetLineGap() const { return m_lineGap; }
		const int& GetFontHeight() const { return m_ascent - m_descent; }
		const int& GetFontLineHeight() const { return m_descent - m_descent + m_lineGap; }
		
		float GetScale(float size) const;
		float GetKerning(int glyph1, int glyph2, float scale) const;
		Character GetCharacter(int glyph, float scale) const;
		bool BlitCharacter(const Character& ch, int outStride, unsigned char** pixels) const;

	private:
		void* m_font;
		unsigned char* m_internalBuffer;
		std::string m_familyName;
		std::string m_styleName;

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