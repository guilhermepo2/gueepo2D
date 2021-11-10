#include "gueepo2Dpch.h"
#include "Vector2.h"

namespace gueepo::math {
	const Vector2 Vector2::Zero(0.0f, 0.0f);
	const Vector2 Vector2::Right(1.0f, 0.0f);
	const Vector2 Vector2::Up(0.0f, 1.0f);
}

gueepo::math::Vector2 gueepo::math::operator*(const float& lhs, const gueepo::math::Vector2& rhs) {
	return gueepo::math::Vector2(
		lhs * rhs.x,
		lhs * rhs.y
	);
}