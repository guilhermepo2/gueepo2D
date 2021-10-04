#include "gueepo2Dpch.h"
#include "File.h"
#include "core/Log.h"

namespace gueepo {

	File::File(const std::string& Filepath) : File(Filepath, std::ios_base::in | std::ios_base::out) {}

	File::File(const std::string& Filepath, std::ios_base::openmode mode) {
		m_File = std::ifstream(Filepath, mode);

		if (!m_File.is_open()) {
			LOG_ERROR("Couldn't open file: {0}", Filepath);
		}
	}

	File::~File() {
		if (IsValid()) {
			m_File.close();
		}
	}

	const std::string File::GetStringContent() {
		std::stringstream sstream;
		sstream << m_File.rdbuf();
		return sstream.str();
	}

	bool File::IsValid() {
		return m_File.is_open();
	}

}