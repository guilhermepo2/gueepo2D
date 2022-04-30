#pragma once
#include <string>

namespace gueepo {
	class filesystem {
	public:
		static bool CreateDirectory(const std::string& path);
		static bool DirectoryExists(const std::string& path);
	};
}
