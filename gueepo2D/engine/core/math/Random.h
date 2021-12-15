#pragma once
#include <random>

namespace gueepo {
	class Random {
	public:
		static void Init() {
			ms_RandomEngine.seed(std::random_device()());
		}

		static float Float() {
			float value = (float)ms_Distribution(ms_RandomEngine) / (float)UINT32_MAX;
			return value;
		}

		static int Int() {
			return ms_Distribution(ms_RandomEngine);
		}

	private:
		static std::mt19937 ms_RandomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> ms_Distribution;
	};
}