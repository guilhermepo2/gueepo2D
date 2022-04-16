#pragma once
#include "Vector2.h"

namespace gueepo {
	namespace math {

		class Rect {
		public:
			Vector2 bottomLeft;
			Vector2 topRight;

			Rect() {}
			Rect(Vector2 _min, Vector2 _max) : bottomLeft(_min), topRight(_max) {}

			Vector2 GetSize() { return topRight - bottomLeft; }
		};

	}
}