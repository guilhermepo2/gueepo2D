#pragma once

namespace gueepo {
	class Color {
	public:
		float rgba[4];

		Color() { SetColor(1.0f, 1.0f, 1.0f, 1.0f); }
		Color(float _r, float _g, float _b, float _a) { SetColor(_r, _g, _b, _a); }
		void SetColor(float _r, float _g, float _b, float _a) { rgba[0] = _r; rgba[1] = _g; rgba[2] = _b; rgba[3] = _a; }
	};
}