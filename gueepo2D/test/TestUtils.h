#pragma once
#include <stdlib.h>
#include <time.h>
#include "core/math/Vector3.h"

namespace gueepo::test {
	void ResetRandomSeed() {
		srand(time(NULL));
	}

	int RandomInt() {
		return rand();
	}

	int RandomInt(int min, int max) {
		return (rand() % max) + min;
	}

	gueepo::math::Vector3 RandomVector() {
		return gueepo::math::Vector3(
			static_cast<float>(RandomInt()),
			static_cast<float>(RandomInt()),
			static_cast<float>(RandomInt())
		);
	}
}
