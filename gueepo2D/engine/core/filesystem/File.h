#pragma once
#include "gueepo2Dpch.h"

namespace gueepo {
	class File {
	public:
		File(const std::string& Filepath);
		File(const std::string& Filepath, std::ios_base::openmode mode);
		~File();

		std::string GetStringContent();
		unsigned char* GetAsUnsignedChar();
		bool IsValid();

	private:
		std::ifstream m_File;
	};
}