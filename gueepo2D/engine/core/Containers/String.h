#pragma once
#include <string>

namespace gueepo {

	class String {
	public:
		String(const char* pIdentString);

		unsigned long HashWithCRC(const char* pIdentString);
		unsigned long GetCRCValue(void) const { return m_crcIdentifier; }
		const std::string& GetString() const { return m_internalString; }

		bool operator< (String const& other) const { return (GetCRCValue() < other.GetCRCValue()); }
		bool operator== (String const& other) const { return GetCRCValue() == other.GetCRCValue(); }

	private:
		unsigned long m_crcIdentifier;
		std::string m_internalString;
	};

}