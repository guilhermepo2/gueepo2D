#pragma once
#include <string>

namespace gueepo {

	class String {
	public:
		String(const char* pIdentString);

		unsigned long HashWithCRC(const char* pIdentString);
		void* HashName(const char* pIdentString);

		unsigned long GetHashValue(void) const { return reinterpret_cast<unsigned long>(m_identifier); }
		unsigned long GetCRCValue(void) const { return m_crcIdentifier; }
		const std::string& GetString() const { return m_internalString; }

		bool operator< (String const& other) const { return (GetHashValue() < other.GetHashValue()); }
		bool operator== (String const& other) const { return GetHashValue() == other.GetHashValue(); }

	private:
		void* m_identifier;
		unsigned long m_crcIdentifier;
		std::string m_internalString;
	};

}