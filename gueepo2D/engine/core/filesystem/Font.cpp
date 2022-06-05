#include "Font.h"
#include "File.h"
#include "core/math/Math.h"

#pragma warning(push, 0)
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#pragma warning(pop)

/*
* Getting a font Name
* This is potentially dangerous and platform specific code?!
* nameId for Microsoft Platforms (https://docs.microsoft.com/en-us/typography/opentype/spec/name)
* 0 => Copyright Notice
* 1 => Font Family
* 2 => Font Subfamily
* 3 => Unique Font Identifier
* 4 => Full font name that reflects all family and relevant subfamily descriptors
* 5 => Version string
* (...) Look at the link, lol
*/
static std::string GetFontName(stbtt_fontinfo* font, int nameId) {
	int length = 0;

	const uint16_t* name = (const uint16_t*)stbtt_GetFontNameString(
		font,
		&length,
		STBTT_PLATFORM_ID_MICROSOFT,
		STBTT_MS_EID_UNICODE_BMP,
		STBTT_MS_LANG_ENGLISH,
		nameId
	);

	// converts utf16 into utf8
	// more info: https://en.wikipedia.org/wiki/UTF-16#Description

	// this really shouldn't be here, do it on a string class, I don't know.
	length /= 2;
	char* buffer = new char[length];
	buffer[0] = '\0';
	size_t bufferLength = 0;

	bool swapEndian = gueepo::math::IsLittleEndian();

	const uint16_t surrogate_min = 0xd800u;
	const uint16_t surrogate_max = 0xdbffu;
	const uint16_t* start = name;
	const uint16_t* end = name + length;

	while ((end == nullptr && *start != 0) || (end != nullptr && start != end)) {
		uint16_t next = (*start++);

		if (swapEndian) {
			next = ((next & 0xff) << 8 | ((next & 0xff00) >> 8));
		}

		uint32_t cp = 0xffff & next;

		if ((cp >= surrogate_min && cp <= surrogate_max)) {
			next = (*start++);

			if (swapEndian) {
				next = ((next & 0xff) << 8 | ((next & 0xff00) >> 8));
			}

			uint32_t trail = 0xffff & next;
			cp = (cp << 10) + trail + 0x10000u - (surrogate_min << 10) - 0xdc00u;
		}

		// append(cp)

		// one octet
		if (cp < 0x80)
		{
			buffer[bufferLength++] = (char)cp;
			buffer[bufferLength] = '\0';
		}
		// two octets
		else if (cp < 0x800)
		{
			buffer[bufferLength++] = (char)((cp >> 6) | 0xc0);
			buffer[bufferLength] = '\0';
			buffer[bufferLength++] = (char)((cp & 0x3f) | 0x80);
			buffer[bufferLength] = '\0';
		}
		// three octets
		else if (cp < 0x10000)
		{
			buffer[bufferLength++] = ((char)((cp >> 12) | 0xe0));
			buffer[bufferLength] = '\0';
			buffer[bufferLength++] = ((char)(((cp >> 6) & 0x3f) | 0x80));
			buffer[bufferLength] = '\0';
			buffer[bufferLength++] = ((char)((cp & 0x3f) | 0x80));
			buffer[bufferLength] = '\0';
		}
		// four octets
		else
		{
			buffer[bufferLength++] = (char)((cp >> 18) | 0xf0);
			buffer[bufferLength] = '\0';
			buffer[bufferLength++] = (char)(((cp >> 12) & 0x3f) | 0x80);
			buffer[bufferLength] = '\0';
			buffer[bufferLength++] = (char)(((cp >> 6) & 0x3f) | 0x80);
			buffer[bufferLength] = '\0';
			buffer[bufferLength++] = (char)((cp & 0x3f) | 0x80);
			buffer[bufferLength] = '\0';
		}
	}

	std::string fontName(buffer);
	
	// delete buffer;
	
	return fontName;
}

namespace gueepo {

	Font::Font() {}
	Font::~Font() {
		if (m_internalBuffer != nullptr) {
			delete m_internalBuffer;
		}
	}

	Font* Font::CreateFont(const std::string& path) {
		File fontFile(path, std::ios_base::in | std::ios_base::binary);
		unsigned char* fontBuffer = fontFile.GetAsUnsignedChar();

		//
		Font* font = new Font();
		

		//
		stbtt_fontinfo* fontInfo = new stbtt_fontinfo();

		if (stbtt_InitFont(fontInfo, fontBuffer, 0) == 0) {
			LOG_WARN("unable to load font {0}!", path);
			return nullptr;
		}

		font->m_font = fontInfo;
		font->m_internalBuffer = fontBuffer;
		font->m_familyName = GetFontName(fontInfo, 1);
		font->m_styleName = GetFontName(fontInfo, 2);
		stbtt_GetFontVMetrics(fontInfo, &font->m_ascent, &font->m_descent, &font->m_lineGap);
		return font;
	}

	float Font::GetScale(float size) const {
		if (m_font == nullptr) {
			return 0.0f;
		}

		return stbtt_ScaleForPixelHeight(static_cast<stbtt_fontinfo*>(m_font), size);
	}

	float Font::GetKerning(int glyph1, int glyph2, float scale) const {
		if (m_font == nullptr) {
			LOG_WARN("trying to get kerning on an invalid font?");
			return 0;
		}

		return stbtt_GetCodepointKernAdvance(static_cast<stbtt_fontinfo*>(m_font), glyph1, glyph2) * scale;

	}

	Character Font::GetCharacter(int glyph, float scale) const {
		Character ch;

		if (m_font == nullptr) {
			LOG_WARN("trying to create a character on an invalid font?");
			return ch;
		}

		int advance, offsetX, x0, y0, x1, y1;

		// Note that each Codepoint call has an alternative Glyph version which caches the work required to lookup the character word[i]
		stbtt_GetCodepointHMetrics(static_cast<stbtt_fontinfo*>(m_font), glyph, &advance, &offsetX);

		// get bounding box for character (may be offset to account for chars that dip above or below the line)
		stbtt_GetCodepointBitmapBox(static_cast<stbtt_fontinfo*>(m_font), glyph, scale, scale, &x0, &y0, &x1, &y1);

		int w = (x1 - x0);
		int h = (y1 - y0);

		ch.glyph = glyph;
		ch.width = w;
		ch.height = h;
		ch.advance = advance;
		ch.offset_x = offsetX * scale;
		ch.offset_y = static_cast<float>(y0);
		ch.scale = scale;
		ch.has_glyph = (w > 0 && h > 0 && stbtt_IsGlyphEmpty(static_cast<stbtt_fontinfo*>(m_font), glyph) == 0);

		return ch;
	}

	bool Font::BlitCharacter(const Character& ch, int outStride, unsigned char** pixels) const {
		unsigned char* src = *pixels;

		stbtt_MakeCodepointBitmap(static_cast<stbtt_fontinfo*>(m_font), src, ch.width, ch.height, outStride, ch.scale, ch.scale, ch.glyph);
		return true;
	}

}