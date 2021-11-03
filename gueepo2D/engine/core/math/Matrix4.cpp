#include "gueepo2Dpch.h"
#include "Matrix4.h"

namespace gueepo::math {
	static float _internal_m4Identity[4][4] = {
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
	};

	const Matrix4 Matrix4::m4Identity(_internal_m4Identity);
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