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
			rect(int x, int y, int width, int height) : bottomLeft(x,y), topRight(width, height) {}

			vec2 GetSize() { return topRight - bottomLeft; }
			bool Contains(float x, float y) const { return (x >= bottomLeft.x && x <= topRight.x && y >= bottomLeft.y && y <= topRight.y); }
			bool Contains(const vec2& point) const { return Contains(point.x, point.y); }
			bool Intersect(rect other) {
				vec2 thisSize = GetSize();
				vec2 otherSize = other.GetSize();
				return (
					bottomLeft.x < other.bottomLeft.x + otherSize.x &&
					bottomLeft.x + thisSize.x > other.bottomLeft.x &&
					bottomLeft.y < other.bottomLeft.y + otherSize.y &&
					bottomLeft.y + thisSize.y > other.bottomLeft.y
					);
			}

			vec2 GetCenter() {
				vec2 size = GetSize();
				return vec2(bottomLeft.x + (size.x / 2), bottomLeft.y + (size.y / 2));
			}
		};

	}
}
