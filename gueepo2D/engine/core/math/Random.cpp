#include "gueepo2Dpch.h"
#include "Random.h"

namespace gueepo {
	std::mt19937 Random::ms_RandomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> Random::ms_Distribution;
}