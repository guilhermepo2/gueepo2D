#pragma once
#include <cmath>

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

		float Magnitude() const {
			return sqrtf( (x*x) + (y*y) + (z*z) );
		}

		float GetLength() const {
			return Magnitude();
		}

		// normalize the vector
		void Normalize() {
			float l = Magnitude();
			x /= l; y /= l; z /= l;
		}
		
		// Returns a normalized copy
		Vector3 GetNormalized() {
			Vector3 normalized(x, y, z);
			normalized.Normalize();
			return normalized;
		}

		Vector3 operator+(const Vector3& other) {
			return Vector3(
				this->x + other.x,
				this->y + other.y,
				this->z + other.z
			);
		}

		Vector3 operator-(const Vector3& other) {
			return Vector3(
				this->x - other.x,
				this->y - other.y,
				this->z - other.z
			);
		}

		Vector3 operator*(const float& scalar) {
			return Vector3(
				this->x * scalar,
				this->y * scalar,
				this->z * scalar
			);
		}

		bool operator==(const Vector3& rhs) const {
			return this->x == rhs.x &&
				this->y == rhs.y &&
				this->z == rhs.z;
		}

		bool operator!=(const Vector3& other) const {
			return this->x != other.x ||
				this->y != other.y ||
				this->z != other.z;
		}

		friend Vector3 operator*(const float& lhs, const Vector3& rhs);

		static float Dot(const Vector3& lhs, const Vector3& rhs) {
			return (
				(lhs.x * rhs.x) +
				(lhs.y * rhs.y) +
				(lhs.z * rhs.z)
			);
		}

		static float Angle(const Vector3& lhs, const Vector3& rhs) {
			float dot = Dot(lhs, rhs);
			float lhsLength = lhs.GetLength();
			float rhsLength = rhs.GetLength();
			return (dot / (lhsLength * rhsLength));
		}

		static Vector3 Cross(const Vector3& lhs, const Vector3& rhs) {
			return Vector3(0.0f);
		}
	};
}

gueepo::math::Vector3 gueepo::math::operator*(const float& lhs, const gueepo::math::Vector3& rhs) {
	return gueepo::math::Vector3(
		lhs * rhs.x,
		lhs * rhs.y,
		lhs * rhs.z
	);
}
