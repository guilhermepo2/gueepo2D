#pragma once

namespace gueepo::math {
	class Vector3 {
	public:
		float x;
		float y;
		float z;

		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(float _v) : x(_v), y(_v), z(_v) {}
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		Vector3(const Vector3& _other) : x(_other.x), y(_other.y), z(_other.z) {}
		// #todo: construct from vector2
	};
}
