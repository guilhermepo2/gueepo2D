#include "Font.h"
#include "File.h"

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

	
	length /= 2;
	char* buffer = new char[length];
	buffer[0] = '\0';
	size_t bufferLength = 0;
	bool swapEndian = true;

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
	LOG_INFO("string name: {0}", fontName);

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
	}
}