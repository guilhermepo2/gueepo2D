#pragma once
#include "core/math/math.h"

namespace gueepo {
	class LineSegment {
	public:
		LineSegment(const math::vec2& start, const math::vec2& end);
		math::vec2 PointOnSegment(float t) const;
		
	private:
		math::vec2 m_start;
		math::vec2 m_end;
	};
}