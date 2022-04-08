#include "gueepo2Dpch.h"
#include "Log.h"

#pragma warning(push, 0)
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#pragma warning(pop)

namespace gueepo {
	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::Initialize() {

		// #todo: route this to gueepo::filesystem
		std::string logsDir = "logs";
		if (!std::filesystem::exists(logsDir)) {
			std::filesystem::create_directories(logsDir);
		}

		std::vector<spdlog::sink_ptr> loggerSinks = {
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
			std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/gueepo2D.log", true)
		};

		loggerSinks[0]->set_pattern("%^[%T%L][%n] %v%$ (%s:%#)");
		loggerSinks[1]->set_pattern("%^[%T%L][%n] %v%$ (%s:%#)");

		s_Logger = std::make_shared<spdlog::logger>("gueepo2D", loggerSinks.begin(), loggerSinks.end());
		s_Logger->set_level(spdlog::level::trace);

		spdlog::set_default_logger(s_Logger);
	}
}
