// ==========================================================================
// hashed_string.h
// 
// A hashed string is an IMMUTABLE string.
// A hash for it is calculated when it is created, using a CRC32 algorithm.
// It's main purpose is to excel at string comparison, storing a string for the game,
// and to aid in localization.
// ==========================================================================

#pragma once
#include <string>

namespace gueepo {

	class hashed_string {
	public:
		hashed_string(const char* pIdentString);

		unsigned long HashWithCRC(const char* pIdentString);
		unsigned long GetCRCValue(void) const { return m_crcIdentifier; }
		const std::string& GetString() const { return m_internalString; }

		bool operator<(const hashed_string& other) const { return (GetCRCValue() < other.GetCRCValue()); }
		bool operator==(const hashed_string& other) const { return GetCRCValue() == other.GetCRCValue(); }

	private:
		unsigned long m_crcIdentifier;
		std::string m_internalString;
	};

}

struct StringHasher {
	unsigned long operator()(const gueepo::hashed_string& k) const {
		return k.GetCRCValue();
	}
};

