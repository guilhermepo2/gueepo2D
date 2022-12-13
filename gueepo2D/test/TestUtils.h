#pragma once
#include <stdlib.h>
#include <time.h>
#include "core/math/vec3.h"

namespace gueepo::test {
	void ResetRandomSeed() {
		srand(time(NULL));
	}

	int RandomInt() {
		return std::rand();
	}

	int RandomInt(int min, int max) {
		return (std::rand() % max) + min;
	}

	gueepo::math::vec3 RandomVector() {
		return gueepo::math::vec3(
			static_cast<float>(RandomInt()),
			static_cast<float>(RandomInt()),
			static_cast<float>(RandomInt())
		);
	}
}
