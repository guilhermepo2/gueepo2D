#pragma once
// #todo precompiled header?
#include <fstream>

namespace gueepo {
	class File {
	public:
		File(const std::string& Filepath);
		File(const std::string& Filepath, std::ios_base::openmode mode);
		~File();

		const std::string GetStringContent();
		bool IsValid();

	private:
		std::ifstream m_File;
	};
}