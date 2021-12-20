#pragma once
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Random.h"
#include <cmath>

namespace gueepo {
	namespace math {

		static const float RAD_TO_DEG = 57.2958f;
		static const float DEG_TO_RAD = 0.0174f;

		static float cos(float theta) {
			return std::cos(theta);
		}

		static float sin(float theta) {
			return std::sin(theta);
		}

		static float abs(float value) {
			return std::abs(value);
		}
	}
}
