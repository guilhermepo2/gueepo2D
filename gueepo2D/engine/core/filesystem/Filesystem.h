#pragma once
#include <string>

namespace gueepo {
	class filesystem {
	public:
		static bool CreateNewDirectory(const std::string& path);
		static bool DirectoryExists(const std::string& path);
	};
}
