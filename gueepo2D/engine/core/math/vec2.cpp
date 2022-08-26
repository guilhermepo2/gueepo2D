#include "gueepo2Dpch.h"
#include "vec2.h"

namespace gueepo::math {
	const vec2 vec2::Zero(0.0f, 0.0f);
	const vec2 vec2::One(1.0f, 1.0f);
	const vec2 vec2::Right(1.0f, 0.0f);
	const vec2 vec2::Up(0.0f, 1.0f);
}

gueepo::math::vec2 gueepo::math::operator*(const float& lhs, const gueepo::math::vec2& rhs) {
	return gueepo::math::vec2(
		lhs * rhs.x,
		lhs * rhs.y
	);
}