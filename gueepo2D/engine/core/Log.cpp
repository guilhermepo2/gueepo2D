#include "gueepo2Dpch.h"
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace gueepo {
	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::Initialize() {
		spdlog::set_pattern("%^[%T%L][%n] %v%$ (%s:%#)");
		s_Logger = spdlog::stdout_color_mt("gueepo2D");
		s_Logger->set_level(spdlog::level::trace);
		spdlog::set_default_logger(s_Logger);
	}
}