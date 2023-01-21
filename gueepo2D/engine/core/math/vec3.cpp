#include "vec3.h"

namespace gueepo::math {
	const vec3 vec3::Zero(0.0f, 0.0f, 0.0f);
	const vec3 vec3::Right(1.0f, 0.0f, 0.0f);
	const vec3 vec3::Up(0.0f, 1.0f, 0.0f);
	const vec3 vec3::Forward(0.0f, 0.0f, 1.0f);
}

gueepo::math::vec3 gueepo::math::operator*(const float& lhs, const gueepo::math::vec3& rhs) {
	return gueepo::math::vec3(
		lhs * rhs.x,
		lhs * rhs.y,
		lhs * rhs.z
	);
}