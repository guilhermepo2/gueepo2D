#pragma once
#include "mat4.h"
#include "rect.h"
#include "vec2.h"
#include "vec3.h"
#include "rand.h"
#include "endian.h"
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

		static float clamp(float value, float min, float max) {
			return std::clamp(value, min, max);
		}

		static float floor(float value) {
			return std::floor(value);
		}

		static float ceil(float value) {
			return std::ceil(value);
		}

		static float round(float value) {
			return std::round(value);
		}

		static float sign(float value) {
			return (value > 0) - (value < 0);
		}
	}
}
