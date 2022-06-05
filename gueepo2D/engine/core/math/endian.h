#pragma once

// https://github.com/NoelFB/blah/blob/master/include/blah/math/calc.h
// https://stackoverflow.com/questions/4181951/how-to-check-whether-a-system-is-big-endian-or-little-endian
/*
int n = 1;
// little endian if true
if (*(char*)&n == 1) { ... }
*/

namespace gueepo {
	namespace math {
		enum class ENDIAN {
			LITTLE,
			BIG
		};

		inline bool IsBigEndian() { 
			int n = 1;
			return (*(char*)&n != 1);
		}

		inline bool IsLittleEndian() {
			int n = 1;
			return (*(char*)&n == 1); 
		}

		inline bool IsEndian(const ENDIAN& endian) {
			return
				(endian == ENDIAN::LITTLE && IsLittleEndian()) ||
				(endian == ENDIAN::BIG && IsBigEndian());
		}
	}
}