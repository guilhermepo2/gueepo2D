#include "gueepo2Dpch.h"
#include "Matrix4.h"
#include "Math.h"

namespace gueepo::math {
	static float _internal_m4Identity[4][4] = {
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
	};

	const Matrix4 Matrix4::m4Identity(_internal_m4Identity);

	gueepo::math::Matrix4 Matrix4::CreateOrtographicProjection(float l, float r, float b, float t, float zNear, float zFar) {
		math::Matrix4 ortographicProjection;

		ortographicProjection.mat[0][0] = (2 / (r - l) );
		ortographicProjection.mat[1][1] = (2 / (t - b) );
		// on the book this is -2, on GLM this is 2... what?
		ortographicProjection.mat[2][2] = (-2 / (zFar - zNear) );
		ortographicProjection.mat[0][3] = (r + l) / (r - l);
		ortographicProjection.mat[1][3] = (t + b) / (t - b);
		ortographicProjection.mat[2][3] = (zFar + zNear) / (zFar - zNear);

		return ortographicProjection;
	}

	gueepo::math::Matrix4 Matrix4::CreateTranslation(const Vector3& translation) {
		Matrix4 translationMatrix;
		translationMatrix.mat[3][0] = translation.x;
		translationMatrix.mat[3][1] = translation.y;
		translationMatrix.mat[3][2] = translation.z;
		return translationMatrix;
	}

	gueepo::math::Matrix4 Matrix4::CreateTranslation(const Vector2& translation) {
		return gueepo::math::Matrix4::CreateTranslation(Vector3(translation.x, translation.y, 0.0f));
	}

	gueepo::math::Matrix4 Matrix4::CreateScale(const Vector3& scale) {
		Matrix4 scaleMatrix;
		scaleMatrix.mat[0][0] = scale.x;
		scaleMatrix.mat[1][1] = scale.y;
		scaleMatrix.mat[2][3] = scale.z;
		scaleMatrix.mat[3][3] = 1.0f;
		return scaleMatrix;
	}

	gueepo::math::Matrix4 Matrix4::CreateScale(const Vector2& scale) {
		return Matrix4::CreateScale(Vector3(scale.x, scale.y, 0.0f));
	}

	gueepo::math::Matrix4 Matrix4::CreateRotation(float rotation) {
		Matrix4 rotationMatrix;
		rotationMatrix.mat[0][0] = cosf(rotation);
		rotationMatrix.mat[0][1] = sinf(rotation);
		rotationMatrix.mat[1][0] = -sinf(rotation);
		rotationMatrix.mat[1][1] = cosf(rotation);
		return rotationMatrix;
	}

	// from game programming in cpp book
	// #todo: TEMP? FIND A BETTER WAY?
	gueepo::math::Matrix4 Matrix4::CreateInverse(const Matrix4& other) {
		float tmp[12];
		float src[16];
		float dst[16];
		float det;

		// Transpose matrix
		// row 1 to col 1
		src[0] = other.mat[0][0];
		src[4] = other.mat[0][1];
		src[8] = other.mat[0][2];
		src[12] = other.mat[0][3];

		// row 2 to col 2
		src[1] = other.mat[1][0];
		src[5] = other.mat[1][1];
		src[9] = other.mat[1][2];
		src[13] = other.mat[1][3];

		// row 3 to col 3
		src[2] = other.mat[2][0];
		src[6] = other.mat[2][1];
		src[10] = other.mat[2][2];
		src[14] = other.mat[2][3];

		// row 4 to col 4
		src[3] = other.mat[3][0];
		src[7] = other.mat[3][1];
		src[11] = other.mat[3][2];
		src[15] = other.mat[3][3];

		// Calculate cofactors
		tmp[0] = src[10] * src[15];
		tmp[1] = src[11] * src[14];
		tmp[2] = src[9] * src[15];
		tmp[3] = src[11] * src[13];
		tmp[4] = src[9] * src[14];
		tmp[5] = src[10] * src[13];
		tmp[6] = src[8] * src[15];
		tmp[7] = src[11] * src[12];
		tmp[8] = src[8] * src[14];
		tmp[9] = src[10] * src[12];
		tmp[10] = src[8] * src[13];
		tmp[11] = src[9] * src[12];

		dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
		dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
		dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
		dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
		dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
		dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
		dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
		dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
		dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
		dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
		dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
		dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
		dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
		dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
		dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
		dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

		tmp[0] = src[2] * src[7];
		tmp[1] = src[3] * src[6];
		tmp[2] = src[1] * src[7];
		tmp[3] = src[3] * src[5];
		tmp[4] = src[1] * src[6];
		tmp[5] = src[2] * src[5];
		tmp[6] = src[0] * src[7];
		tmp[7] = src[3] * src[4];
		tmp[8] = src[0] * src[6];
		tmp[9] = src[2] * src[4];
		tmp[10] = src[0] * src[5];
		tmp[11] = src[1] * src[4];

		dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
		dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
		dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
		dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
		dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
		dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
		dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
		dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
		dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
		dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
		dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
		dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
		dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
		dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
		dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
		dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

		// Calculate determinant
		det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];

		// Inverse of matrix is divided by determinant
		det = 1 / det;
		for (int j = 0; j < 16; j++)
		{
			dst[j] *= det;
		}

		// Creating the new matrix
		Matrix4 inverseMatrix;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				inverseMatrix.mat[i][j] = dst[i * 4 + j];
			}
		}

		return inverseMatrix;
	}

}

gueepo::math::Vector3 gueepo::math::operator*(const gueepo::math::Matrix4& m, const gueepo::math::Vector3& other) {
	Vector3 returnValue;
	returnValue.x = (m.mat[0][0] * other.x) + (m.mat[1][0] * other.y) + (m.mat[2][0] * other.z) + (m.mat[3][0] * 1);
	returnValue.y = (m.mat[0][1] * other.x) + (m.mat[1][1] * other.y) + (m.mat[2][1] * other.z) + (m.mat[3][1] * 1);
	returnValue.z = (m.mat[0][2] * other.x) + (m.mat[1][2] * other.y) + (m.mat[2][2] * other.z) + (m.mat[3][2] * 1);

	return returnValue;
}

gueepo::math::Matrix4 gueepo::math::operator*(const float& lhs, const gueepo::math::Matrix4& rhs) {
	gueepo::math::Matrix4 ret;
	ret.mat[0][0] = rhs.mat[0][0] * lhs;
	ret.mat[0][1] = rhs.mat[0][1] * lhs;
	ret.mat[0][2] = rhs.mat[0][2] * lhs;
	ret.mat[0][3] = rhs.mat[0][3] * lhs;

	ret.mat[1][0] = rhs.mat[1][0] * lhs;
	ret.mat[1][1] = rhs.mat[1][1] * lhs;
	ret.mat[1][2] = rhs.mat[1][2] * lhs;
	ret.mat[1][3] = rhs.mat[1][3] * lhs;

	ret.mat[2][0] = rhs.mat[2][0] * lhs;
	ret.mat[2][1] = rhs.mat[2][1] * lhs;
	ret.mat[2][2] = rhs.mat[2][2] * lhs;
	ret.mat[2][3] = rhs.mat[2][3] * lhs;

	ret.mat[3][0] = rhs.mat[3][0] * lhs;
	ret.mat[3][1] = rhs.mat[3][1] * lhs;
	ret.mat[3][2] = rhs.mat[3][2] * lhs;
	ret.mat[3][3] = rhs.mat[3][3] * lhs;
	return ret;
}