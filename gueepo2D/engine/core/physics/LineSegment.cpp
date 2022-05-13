#include "gueepo2Dpch.h"
#include "LineSegment.h"

namespace gueepo {

	LineSegment::LineSegment(const math::vec2& start, const math::vec2& end) : m_start(start), m_end(end) {}

	gueepo::math::vec2 LineSegment::PointOnSegment(float t) const {
		t = math::clamp(t, 0.0f, 1.0f);
		return m_start + ((m_end - m_start) * t);
	}
}