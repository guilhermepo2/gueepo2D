#pragma once
#include "vec2.h"
#include "vec3.h"
#include <string> // memcpy

namespace gueepo::math {
	class mat4 {
	public:
		float mat[4][4];

		mat4() {
			*this = mat4::m4Identity;
		}

		explicit mat4(float inMat[4][4]) {
			memcpy(mat, inMat, 16 * sizeof(float));
		}

		const float* GetValueData() {
			return reinterpret_cast<const float*>(&mat[0][0]);
		}

		mat4 operator+(const mat4& other) {
			mat4 ret;
			ret.mat[0][0] = mat[0][0] + other.mat[0][0];
			ret.mat[0][1] = mat[0][1] + other.mat[0][1];
			ret.mat[0][2] = mat[0][2] + other.mat[0][2];
			ret.mat[0][3] = mat[0][3] + other.mat[0][3];

			ret.mat[1][0] = mat[1][0] + other.mat[1][0];
			ret.mat[1][1] = mat[1][1] + other.mat[1][1];
			ret.mat[1][2] = mat[1][2] + other.mat[1][2];
			ret.mat[1][3] = mat[1][3] + other.mat[1][3];

			ret.mat[2][0] = mat[2][0] + other.mat[2][0];
			ret.mat[2][1] = mat[2][1] + other.mat[2][1];
			ret.mat[2][2] = mat[2][2] + other.mat[2][2];
			ret.mat[2][3] = mat[2][3] + other.mat[2][3];

			ret.mat[3][0] = mat[3][0] + other.mat[3][0];
			ret.mat[3][1] = mat[3][1] + other.mat[3][1];
			ret.mat[3][2] = mat[3][2] + other.mat[3][2];
			ret.mat[3][3] = mat[3][3] + other.mat[3][3];
			return ret;
		}

		mat4 operator-(const mat4& other) {
			mat4 ret;
			ret.mat[0][0] = mat[0][0] - other.mat[0][0];
			ret.mat[0][1] = mat[0][1] - other.mat[0][1];
			ret.mat[0][2] = mat[0][2] - other.mat[0][2];
			ret.mat[0][3] = mat[0][3] - other.mat[0][3];

			ret.mat[1][0] = mat[1][0] - other.mat[1][0];
			ret.mat[1][1] = mat[1][1] - other.mat[1][1];
			ret.mat[1][2] = mat[1][2] - other.mat[1][2];
			ret.mat[1][3] = mat[1][3] - other.mat[1][3];

			ret.mat[2][0] = mat[2][0] - other.mat[2][0];
			ret.mat[2][1] = mat[2][1] - other.mat[2][1];
			ret.mat[2][2] = mat[2][2] - other.mat[2][2];
			ret.mat[2][3] = mat[2][3] - other.mat[2][3];

			ret.mat[3][0] = mat[3][0] - other.mat[3][0];
			ret.mat[3][1] = mat[3][1] - other.mat[3][1];
			ret.mat[3][2] = mat[3][2] - other.mat[3][2];
			ret.mat[3][3] = mat[3][3] - other.mat[3][3];
			return ret;
		}

		mat4 operator*(const float& scalar) {
			mat4 ret;
			ret.mat[0][0] = mat[0][0] * scalar;
			ret.mat[0][1] = mat[0][1] * scalar;
			ret.mat[0][2] = mat[0][2] * scalar;
			ret.mat[0][3] = mat[0][3] * scalar;

			ret.mat[1][0] = mat[1][0] * scalar;
			ret.mat[1][1] = mat[1][1] * scalar;
			ret.mat[1][2] = mat[1][2] * scalar;
			ret.mat[1][3] = mat[1][3] * scalar;

			ret.mat[2][0] = mat[2][0] * scalar;
			ret.mat[2][1] = mat[2][1] * scalar;
			ret.mat[2][2] = mat[2][2] * scalar;
			ret.mat[2][3] = mat[2][3] * scalar;

			ret.mat[3][0] = mat[3][0] * scalar;
			ret.mat[3][1] = mat[3][1] * scalar;
			ret.mat[3][2] = mat[3][2] * scalar;
			ret.mat[3][3] = mat[3][3] * scalar;
			return ret;
		}

		friend vec3 operator*(const mat4& m, const vec3& other);

		friend mat4 operator*(const float& lhs, const mat4& rhs);

		// multiplying matrices, not fun!
		friend mat4 operator*(const mat4& lhs, const mat4& rhs) {
			mat4 ret;

			ret.mat[0][0] =
				lhs.mat[0][0] * rhs.mat[0][0] +
				lhs.mat[0][1] * rhs.mat[1][0] +
				lhs.mat[0][2] * rhs.mat[2][0] +
				lhs.mat[0][3] * rhs.mat[3][0];

			ret.mat[0][1] =
				lhs.mat[0][0] * rhs.mat[0][1] +
				lhs.mat[0][1] * rhs.mat[1][1] +
				lhs.mat[0][2] * rhs.mat[2][1] +
				lhs.mat[0][3] * rhs.mat[3][1];

			ret.mat[0][2] =
				lhs.mat[0][0] * rhs.mat[0][2] +
				lhs.mat[0][1] * rhs.mat[1][2] +
				lhs.mat[0][2] * rhs.mat[2][2] +
				lhs.mat[0][3] * rhs.mat[3][2];

			ret.mat[0][3] =
				lhs.mat[0][0] * rhs.mat[0][3] +
				lhs.mat[0][1] * rhs.mat[1][3] +
				lhs.mat[0][2] * rhs.mat[2][3] +
				lhs.mat[0][3] * rhs.mat[3][3];

			ret.mat[1][0] =
				lhs.mat[1][0] * rhs.mat[0][0] +
				lhs.mat[1][1] * rhs.mat[1][0] +
				lhs.mat[1][2] * rhs.mat[2][0] +
				lhs.mat[1][3] * rhs.mat[3][0];
			ret.mat[1][1] =
				lhs.mat[1][0] * rhs.mat[0][1] +
				lhs.mat[1][1] * rhs.mat[1][1] +
				lhs.mat[1][2] * rhs.mat[2][1] +
				lhs.mat[1][3] * rhs.mat[3][1];
			ret.mat[1][2] =
				lhs.mat[1][0] * rhs.mat[0][2] +
				lhs.mat[1][1] * rhs.mat[1][2] +
				lhs.mat[1][2] * rhs.mat[2][2] +
				lhs.mat[1][3] * rhs.mat[3][2];
			ret.mat[1][3] =
				lhs.mat[1][0] * rhs.mat[0][3] +
				lhs.mat[1][1] * rhs.mat[1][3] +
				lhs.mat[1][2] * rhs.mat[2][3] +
				lhs.mat[1][3] * rhs.mat[3][3];

			ret.mat[2][0] =
				lhs.mat[2][0] * rhs.mat[0][0] +
				lhs.mat[2][1] * rhs.mat[1][0] +
				lhs.mat[2][2] * rhs.mat[2][0] +
				lhs.mat[2][3] * rhs.mat[3][0];
			ret.mat[2][1] =
				lhs.mat[2][0] * rhs.mat[0][1] +
				lhs.mat[2][1] * rhs.mat[1][1] +
				lhs.mat[2][2] * rhs.mat[2][1] +
				lhs.mat[2][3] * rhs.mat[3][1];
			ret.mat[2][2] =
				lhs.mat[2][0] * rhs.mat[0][2] +
				lhs.mat[2][1] * rhs.mat[1][2] +
				lhs.mat[2][2] * rhs.mat[2][2] +
				lhs.mat[2][3] * rhs.mat[3][2];
			ret.mat[2][3] =
				lhs.mat[2][0] * rhs.mat[0][3] +
				lhs.mat[2][1] * rhs.mat[1][3] +
				lhs.mat[2][2] * rhs.mat[2][3] +
				lhs.mat[2][3] * rhs.mat[3][3];

			ret.mat[3][0] =
				lhs.mat[3][0] * rhs.mat[0][0] +
				lhs.mat[3][1] * rhs.mat[1][0] +
				lhs.mat[3][2] * rhs.mat[2][0] +
				lhs.mat[3][3] * rhs.mat[3][0];
			ret.mat[3][1] =
				lhs.mat[3][0] * rhs.mat[0][1] +
				lhs.mat[3][1] * rhs.mat[1][1] +
				lhs.mat[3][2] * rhs.mat[2][1] +
				lhs.mat[3][3] * rhs.mat[3][1];
			ret.mat[3][2] =
				lhs.mat[3][0] * rhs.mat[0][2] +
				lhs.mat[3][1] * rhs.mat[1][2] +
				lhs.mat[3][2] * rhs.mat[2][2] +
				lhs.mat[3][3] * rhs.mat[3][2];
			ret.mat[3][3] =
				lhs.mat[3][0] * rhs.mat[0][3] +
				lhs.mat[3][1] * rhs.mat[1][3] +
				lhs.mat[3][2] * rhs.mat[2][3] +
				lhs.mat[3][3] * rhs.mat[3][3];

			return ret;
		}

		// #todo: Matrix4 GetInverse()
		// #todo: transform operations (translate, rotate, scale)

		// from Mathematics for 3D Game Programming and Computer Graphics
		static mat4 CreateOrtographicProjection(float l, float r, float b, float t, float zFar = -10.0f, float zNear = 10.0f);
		static mat4 CreateTranslation(const vec3& translation);
		static mat4 CreateTranslation(const vec2& translation);
		static mat4 CreateScale(const vec3& scale);
		static mat4 CreateScale(const vec2& scale);
		static mat4 CreateRotation(float rotation);
		static mat4 CreateInverse(const mat4& other);

		static const mat4 m4Identity;
	};
}