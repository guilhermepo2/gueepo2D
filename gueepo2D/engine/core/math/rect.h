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
			bool Contains(float x, float y) const { return (x >= bottomLeft.x && x <= topRight.x && y >= bottomLeft.y && y <= topRight.y); }
			bool Contains(const vec2& point) const { return Contains(point.x, point.y); }
		};

	}
}
