#pragma once
#include <cstdint>

namespace gueepo::timestep {
	uint32_t GetTicks();
	void Sleep(int milliseconds);
}