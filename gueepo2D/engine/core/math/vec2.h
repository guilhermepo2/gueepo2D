#pragma once
#include <cmath>

namespace gueepo::math {
	class vec2 {
	public:
		float x;
		float y;

		vec2() : x(0.0f), y(0.0f) {}
		vec2(float _v) : x(_v), y(_v) {}
		vec2(float _x, float _y) : x(_x), y(_y) {}
		vec2(const vec2& _other) : x(_other.x), y(_other.y) {}

		float Magnitude() const { return sqrtf( (x*x) + (y*y) ); }
		float GetLength() const { return Magnitude(); }

		void Normalize() {
			float l = Magnitude();
			x /= l;
			y /= l;
		}

		vec2 GetNormalized() {
			vec2 normalized(x, y);
			normalized.Normalize();
			return normalized;
		}

		vec2 operator+(const vec2& other) {
			return vec2(
				this->x + other.x,
				this->y + other.y
			);
		}

		vec2 operator-(const vec2& other) {
			return vec2(
				this->x - other.x,
				this->y - other.y
			);
		}

		friend vec2 operator+(const vec2& a, const vec2& b) {
			return vec2(a.x + b.x, a.y + b.y);
		}

		friend vec2 operator-(const vec2& a, const vec2& b) {
			return vec2(a.x - b.x, a.y - b.y);
		}

		vec2 operator*(const float& scalar) {
			return vec2(
				this->x * scalar,
				this->y * scalar
			);
		}

		friend vec2 operator*(const float& lhs, const vec2& rhs);

		bool operator==(const vec2& rhs) const {
			return this->x == rhs.x && this->y == rhs.y;
		}

		bool operator!=(const vec2& rhs) const {
			return this->x != rhs.x || this->y != rhs.y;
		}

		static float Dot(const vec2& lhs, const vec2& rhs) {
			return (
				(lhs.x * rhs.x) + (lhs.y * rhs.y)
				);
		}

		static const vec2 Zero;
		static const vec2 One;
		static const vec2 Right;
		static const vec2 Up;
	};
}