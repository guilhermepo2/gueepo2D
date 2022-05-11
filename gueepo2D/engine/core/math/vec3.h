#pragma once
#include <cmath>

namespace gueepo::math {
	class vec3 {
	public:
		float x;
		float y;
		float z;

		vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		vec3(float _v) : x(_v), y(_v), z(_v) {}
		vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		vec3(const vec3& _other) : x(_other.x), y(_other.y), z(_other.z) {}
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
		vec3 GetNormalized() {
			vec3 normalized(x, y, z);
			normalized.Normalize();
			return normalized;
		}

		vec3 operator+(const vec3& other) {
			return vec3(
				this->x + other.x,
				this->y + other.y,
				this->z + other.z
			);
		}

		vec3 operator-(const vec3& other) {
			return vec3(
				this->x - other.x,
				this->y - other.y,
				this->z - other.z
			);
		}

		vec3 operator*(const float& scalar) {
			return vec3(
				this->x * scalar,
				this->y * scalar,
				this->z * scalar
			);
		}

		bool operator==(const vec3& rhs) const {
			return this->x == rhs.x &&
				this->y == rhs.y &&
				this->z == rhs.z;
		}

		bool operator!=(const vec3& other) const {
			return this->x != other.x ||
				this->y != other.y ||
				this->z != other.z;
		}

		friend vec3 operator*(const float& lhs, const vec3& rhs);

		static float Dot(const vec3& lhs, const vec3& rhs) {
			return (
				(lhs.x * rhs.x) +
				(lhs.y * rhs.y) +
				(lhs.z * rhs.z)
			);
		}

		static vec3 Cross(const vec3& lhs, const vec3& rhs) {
			return vec3(
				(lhs.y * rhs.z) - (lhs.z * rhs.y),
				(lhs.z * rhs.x) - (lhs.x * rhs.z),
				(lhs.x * rhs.y) - (lhs.y * rhs.x)
			);
		}

		static const vec3 Zero;
		static const vec3 Right;
		static const vec3 Up;
		static const vec3 Forward;
	};
}
