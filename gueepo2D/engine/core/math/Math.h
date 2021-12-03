#pragma once
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

namespace gueepo {
	namespace math {

		static const float RAD_TO_DEG = 57.2958f;
		static const float DEG_TO_RAD = 0.0174f;

		static float cosf(float theta) {
			return cos(theta);
		}

		static float sinf(float theta) {
			return sin(theta);
		}
	}
}
