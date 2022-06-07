#include "gueepo2Dpch.h"
#include "string.h"
#include <string.h>

namespace gueepo {

	char string::emptyBuffer[1] = { '\0' };

	bool string::operator==(const string& rhs) const { return strcmp(c_str(), rhs.c_str()) == 0; }
	bool string::operator!=(const string& rhs) const { return strcmp(c_str(), rhs.c_str()) != 0; }
	bool string::operator==(const char* rhs) const { return strcmp(c_str(), rhs) == 0; }
	bool string::operator!=(const char* rhs) const { return strcmp(c_str(), rhs) != 0; }

	string& string::append(char c) {
		reserve(m_length + 1);
		data()[m_length++] = c;
		data()[m_length] = '\0';
		return *this;
	}

	string& string::append(uint32_t c) {
		// one octet
		if (c < 0x80) {
			append((char)c);
		}
		// two octets
		else if (c < 0x800) {
			append((char)((c >> 6) | 0xc0));
			append((char)((c & 0x3f) | 0x80));
		}
		// three octets
		else if (c < 0x10000) {
			append((char)((c >> 12) | 0xe0));
			append((char)(((c >> 6) & 0x3f) | 0x80));
			append((char)((c & 0x3f) | 0x80));
		}
		// four octets
		else {
			append((char)((c >> 18) | 0xf0));
			append((char)(((c >> 12) & 0x3f) | 0x80));
			append((char)(((c >> 6) & 0x3f) | 0x80));
			append((char)((c & 0x3f) | 0x80));
		}

		return *this;
	}

	// ***********************************************************************
	// UTF8 AND UTF16 SHENANIGANS
	// ***********************************************************************
	uint32_t string::utf8_at(int index) const {
		// TODO: not gonna lie I don't much of an idea of what's happening here.

		uint32_t charcode = 0;
		int t = (unsigned char)(this->operator[](index++));
		if (t < 128) {
			return t;
		}

		int highBitMask = (1 << 6) - 1;
		int highBitShift = 0;
		int totalBits = 0;
		int otherBits = 6;
		
		while ((t & 0xC0) == 0xC0) {
			t <<= 1;
			t &= 0xff;
			totalBits += 6;
			highBitMask >>= 1;
			highBitShift++;
			charcode <<= otherBits;
			charcode |= ((unsigned char)(this->operator[](index++))) & ((1 << otherBits) - 1);
		}

		charcode |= ((t >> highBitShift) & highBitMask) << totalBits;
		return charcode;
	}

	// ***********************************************************************
	int string::utf8_length(int index) const {
		auto c = this->operator[](index);

		if ((c & 0xFE) == 0xFC) { return 6; }
		if ((c & 0xFC) == 0xF8) { return 5; }
		if ((c & 0xF8) == 0xF0) { return 4; }
		if ((c & 0xF0) == 0xE0) { return 3; }
		if ((c & 0xE0) == 0xC0) { return 2; }
		return 1;
	}

	// ***********************************************************************
	gueepo::string& string::append_utf16(const uint16_t* start, const uint16_t* end, bool swapEndian) {
		const uint16_t surrogateMin = 0xd800u;
		const uint16_t surrogateMax = 0xdbffu;

		while ((end == nullptr && *start != 0) || (end != nullptr && start != end)) {
			uint16_t next = (*start++);
			if (swapEndian) {
				next = ((next & 0xff) << 8 | ((next & 0xff00) >> 8));
			}

			uint32_t cp = 0xffff & next;

			if ((cp >= surrogateMin && cp <= surrogateMax)) {
				next = (*start++);

				if (swapEndian) {
					next = ((next & 0xff) << 8 | ((next & 0xff00) >> 8));
				}

				uint32_t trail = 0xffff & next;
				cp = (cp << 10) + trail + 0x10000u - (surrogateMin << 10) - 0xdc00u;
			}

			append(cp);
		}

		return *this;
	}

	// ***********************************************************************
	void string::reserve(int capacity) {
		int bufferLength = capacity + 1;

		if (bufferLength > m_capacity) {
			if (m_capacity <= 0) {
				m_capacity = 16;
			}

			while (m_capacity < bufferLength) {
				m_capacity *= 2;
			}

			// expanding from null or empty buffer
			if (m_buffer == nullptr || m_buffer == emptyBuffer) {
				m_buffer = new char[m_capacity];
				m_buffer[0] = '\0';
			}
			else { // expand from existing buffer
				char* newBuffer = new char[m_capacity];
				memcpy(newBuffer, m_buffer, m_length);
				newBuffer[m_length] = '\0';
				delete[] m_buffer;
				m_buffer = newBuffer;
			}
		}
	}

	// ***********************************************************************
	void string::clear() {
		if (m_capacity > 0) {
			data()[0] = '\0';
		}

		m_length = 0;
	}

	// ***********************************************************************
	void string::set(const char* start, const char* end) {
		if (end == nullptr) {
			end = start + strlen(start);
		}

		int length = (int)(end - start);
		if (length <= 0) {
			clear();
		}
		else {
			m_length = length;
			reserve(m_length);
			char* ptr = data();
			memcpy(ptr, start, m_length);
			ptr[m_length] = '\0';
		}
	}


}