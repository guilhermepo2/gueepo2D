#pragma once
#include "mat4.h"
#include "rect.h"
#include "vec2.h"
#include "vec3.h"
#include "rand.h"
#include "endian.h"
#include <cmath>

#define max_def(a,b)            (((a) > (b)) ? (a) : (b))
#define min_def(a,b)            (((a) < (b)) ? (a) : (b))

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

		static int sign(float value) {
			return (value > 0) - (value < 0);
		}

		static float maximum(float a, float b) {
			return max_def(a, b);
		}

		static float minimum(float a, float b) {
			return min_def(a, b);
		}

		static int ManhattanDistance(math::vec2 a, math::vec2 b) {
			return static_cast<int>(abs(b.x - a.x) + abs(b.y - a.y));
		}
	}
}
