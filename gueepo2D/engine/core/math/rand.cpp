#include "rand.h"

namespace gueepo {
	std::mt19937 rand::ms_RandomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> rand::ms_Distribution;
}