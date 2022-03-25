#include "gueepo2Dpch.h"
#include "String.h"

unsigned reverse(unsigned x) {
	x = ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
	x = ((x & 0x33333333) << 2) | ((x >> 2) & 0x33333333);
	x = ((x & 0x0F0F0F0F) << 4) | ((x >> 4) & 0x0F0F0F0F);
	x = (x << 24) | ((x & 0xFF00) << 8) |
		((x >> 8) & 0xFF00) | (x >> 24);
	return x;
}

namespace gueepo {

	String::String(const char* pIdentString) : m_identifier(HashName(pIdentString)), m_crcIdentifier(HashWithCRC(pIdentString)), m_internalString(pIdentString) {}
	
	// ---------------------------------------------------------------------------------------
	// https://stackoverflow.com/questions/34153765/generate-checksum-for-string
	// ---------------------------------------------------------------------------------------
	unsigned long String::HashWithCRC(const char* pIdentString) {
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
	void* String::HashName(const char* pIdentString) {
		unsigned long BASE = 65521L;
		unsigned long NMAX = 5552;

#define DO1(buf, i) { s1 += tolower(buf[i]); s2 += s1;}
#define DO2(buf, i) DO1(buf, i); DO1(buf, i+1);
#define DO4(buf, i) DO2(buf, i); DO2(buf, i+2);
#define DO8(buf, i) DO4(buf, i); DO4(buf, i+4);
#define DO16(buf) DO8(buf, 0); DO8(buf, 8);

		if (pIdentString == nullptr) {
			return nullptr;
		}

		unsigned long s1 = 0;
		unsigned long s2 = 0;

		for (size_t len = strlen(pIdentString); len > 0; /* x */) {
			unsigned long k = len < NMAX ? len : NMAX;
			len -= k;

			while (k >= 16) {
				DO16(pIdentString);
				pIdentString += 16;
				k -= 16;
			}

			if (k != 0) {
				do {
					s1 += tolower(*pIdentString++);
					s2 += s1;
				} while (--k);
			}

			s1 %= BASE;
			s2 %= BASE;
		}

		return reinterpret_cast<void*>((s2 << 16) | s1);

#undef DO1
#undef DO2
#undef DO4
#undef DO8
#undef DO16
	}
}