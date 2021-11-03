#pragma once

namespace gueepo::math {
	class Matrix4 {
	public:
		float mat[4][4];

		Matrix4() {
			*this = Matrix4::m4Identity;
		}

		explicit Matrix4(float inMat[4][4]) {
			memcpy(mat, inMat, 16 * sizeof(float));
		}

		const float* GetValueData() {
			return reinterpret_cast<const float*>(&mat[0][0]);
		}

		Matrix4 operator+(const Matrix4& other) {
			Matrix4 ret;
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

		Matrix4 operator-(const Matrix4& other) {
			Matrix4 ret;
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

		Matrix4 operator*(const float& scalar) {
			Matrix4 ret;
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

		friend Matrix4 operator*(const float& lhs, const Matrix4& rhs);

		// multiplying matrices, not fun!
		friend Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs) {
			Matrix4 ret;

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

		static const Matrix4 m4Identity;
	};
}