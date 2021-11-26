#include "gueepo2Dpch.h"
#include "Vector3.h"

namespace gueepo::math {
	const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);
}

gueepo::math::Vector3 gueepo::math::operator*(const float& lhs, const gueepo::math::Vector3& rhs) {
	return gueepo::math::Vector3(
		lhs * rhs.x,
		lhs * rhs.y,
		lhs * rhs.z
	);
}