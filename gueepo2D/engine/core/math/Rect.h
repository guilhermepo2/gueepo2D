#pragma once
#include "vec2.h"

namespace gueepo {
	namespace math {

		class rect {
		public:
			vec2 bottomLeft;
			vec2 topRight;

			rect() {}
			rect(vec2 _min, vec2 _max) : bottomLeft(_min), topRight(_max) {}

			vec2 GetSize() { return topRight - bottomLeft; }
		};

	}
}