#pragma once

// =====================================================================================================
// Profiler.h
// Define some common and basic functionality to profile code
// Timer and Scoped Timer: https://github.com/TheCherno/Walnut/blob/master/Walnut/src/Walnut/Timer.h
// =====================================================================================================

#ifdef GUEEPO2D_DEBUG
#include "core/Log.h"
#include <chrono>
#include <string>
namespace gueepo::debug {
	class Timer {
	public:
		Timer() { Reset(); }
		void Reset() { m_Start = std::chrono::high_resolution_clock::now(); }
		float Ellapsed() { return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f; }
		float Milliseconds() { return Ellapsed() * 1000.0f; }
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};

	class ScopedTimer {
	public:
		ScopedTimer(const std::string& name) : m_Name(name) {}
		~ScopedTimer() {
			float time = m_Timer.Milliseconds();
			LOG_INFO("[debug::TIMER] {0}: {1}ms", m_Name, time);
		}
	private:
		std::string m_Name;
		Timer m_Timer;
	};
}

#define GUEEPO2D_SCOPED_TIMER(x) gueepo::debug::ScopedTimer s(x)

#else

#define GUEEPO2D_SCOPED_TIMER(x) 

#endif