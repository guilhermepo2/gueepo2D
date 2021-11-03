#pragma once
#include <cmath>

namespace gueepo::math {
	class Vector2 {
	public:
		float x;
		float y;

		Vector2() : x(0.0f), y(0.0f) {}
		Vector2(float _v) : x(_v), y(_v) {}
		Vector2(float _x, float _y) : x(_x), y(_y) {}
		Vector2(const Vector2& _other) : x(_other.x), y(_other.y) {}

		float Magnitude() const { return sqrtf( (x*x) + (y*y) ); }
		float GetLength() const { return Magnitude(); }

		void Normalize() {
			float l = Magnitude();
			x /= l;
			y /= l;
		}

		Vector2 GetNormalized() {
			Vector2 normalized(x, y);
			normalized.Normalize();
			return normalized;
		}

		Vector2 operator+(const Vector2& other) {
			return Vector2(
				this->x + other.x,
				this->y + other.y
			);
		}

		Vector2 operator-(const Vector2& other) {
			return Vector2(
				this->x - other.x,
				this->y - other.y
			);
		}

		Vector2 operator*(const float& scalar) {
			return Vector2(
				this->x * scalar,
				this->y * scalar
			);
		}

		friend Vector2 operator*(const float& lhs, const Vector2& rhs);

		bool operator==(const Vector2& rhs) const {
			return this->x == rhs.x && this->y == rhs.y;
		}

		bool operator!=(const Vector2& rhs) const {
			return this->x != rhs.x || this->y != rhs.y;
		}

		static float Dot(const Vector2& lhs, const Vector2& rhs) {
			return (
				(lhs.x * rhs.x) + (lhs.y * rhs.y)
				);
		}

		static const Vector2 Zero;
		static const Vector2 Right;
		static const Vector2 Up;
	};
}

gueepo::math::Vector2 gueepo::math::operator*(const float& lhs, const Vector2& rhs) {
	return gueepo::math::Vector2(
		lhs * rhs.x,
		lhs * rhs.y
	);
}