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
