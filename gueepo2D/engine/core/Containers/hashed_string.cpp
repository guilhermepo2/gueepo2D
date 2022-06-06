// ==========================================================================
// hashed_string.cpp
// 
// A hashed string is an IMMUTABLE string.
// A hash for it is calculated when it is created, using a CRC32 algorithm.
// It's main purpose is to excel at string comparison, storing a string for the game,
// and to aid in localization.
// ==========================================================================

#include "gueepo2Dpch.h"
#include "hashed_string.h"

static unsigned reverse(unsigned x) {
	x = ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
	x = ((x & 0x33333333) << 2) | ((x >> 2) & 0x33333333);
	x = ((x & 0x0F0F0F0F) << 4) | ((x >> 4) & 0x0F0F0F0F);
	x = (x << 24) | ((x & 0xFF00) << 8) |
		((x >> 8) & 0xFF00) | (x >> 24);
	return x;
}

namespace gueepo {

	hashed_string::hashed_string(const char* pIdentString) : m_crcIdentifier(HashWithCRC(pIdentString)), m_internalString(pIdentString) {}
	
	// ---------------------------------------------------------------------------------------
	// https://stackoverflow.com/questions/34153765/generate-checksum-for-string
	// ---------------------------------------------------------------------------------------
	unsigned long hashed_string::HashWithCRC(const char* pIdentString) {
		int i, j;
		unsigned long byte, crc;

		i = 0;
		crc = 0xFFFFFFFF;
		while (pIdentString[i] != 0) {
			byte = pIdentString[i];            // Get next byte.
			byte = reverse(byte);         // 32-bit reversal.
			for (j = 0; j <= 7; j++) {    // Do eight times.
				if ((int)(crc ^ byte) < 0)
					crc = (crc << 1) ^ 0x04C11DB7;
				else crc = crc << 1;
				byte = byte << 1;          // Ready next msg bit.
			}
			i = i + 1;
		}
		return reverse(~crc);
	}

	// ---------------------------------------------------------------------------------------
	// https://github.com/MikeMcShaffry/gamecode4/blob/master/Source/GCC4/Utilities/String.cpp
	// ---------------------------------------------------------------------------------------
}