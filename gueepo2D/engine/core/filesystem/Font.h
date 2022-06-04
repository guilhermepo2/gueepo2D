#pragma once
#include <string>

namespace gueepo {
	class Font {
	public:
		Font();
		~Font();

		static Font* CreateFont(const std::string& path);

	private:
		void* m_font;
		unsigned char* m_internalBuffer;
		std::string m_familyName;
		std::string m_styleName;
	};
}