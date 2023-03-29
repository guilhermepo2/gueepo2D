#include "File.h"
#include "core/Log.h"
#include <sstream>

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

	std::string File::GetStringContent() {
		std::stringstream sstream;
		sstream << m_File.rdbuf();
		return sstream.str();
	}

	unsigned char* File::GetAsUnsignedChar() {
		LOG_WARN("(File::GetAsUnsignedChar) the application is responsible for freeing the memory that is allocated here.");

		std::filebuf* pbuf = m_File.rdbuf();
		std::size_t size = pbuf->pubseekoff(0, m_File.end, m_File.in);
		pbuf->pubseekpos(0, m_File.in);
		unsigned char* fontBuffer = new unsigned char[size];
		pbuf->sgetn( (char*)(&fontBuffer[0]) , size);

		return fontBuffer;
	}

	bool File::IsValid() {
		return m_File.is_open();
	}

}