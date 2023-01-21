#include "gueepo2Dpch.h"
#include "Filesystem.h"
#include <filesystem>

namespace gueepo {
	bool filesystem::CreateNewDirectory(const std::string& path) {
		return std::filesystem::create_directories(path);
	}

	bool filesystem::DirectoryExists(const std::string& path) {
		return std::filesystem::exists(path);
	}
}