#pragma once
#include "Vector2.h"

namespace gueepo {
	namespace math {

		class Rect {
		public:
			Vector2 min;
			Vector2 max;

			Vector2 GetSize() {
				return max - min;
			}
		};

	}
}