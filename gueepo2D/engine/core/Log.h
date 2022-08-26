#pragma once

// The warning pragma also supports the following syntax, where the optional n parameter represents a warning level (1 through 4).
// from: https://docs.microsoft.com/en-us/cpp/preprocessor/warning?view=msvc-160
// 0 will ignore all warnings from here
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace gueepo {

	class Log {
	public:
		static void Initialize();
		static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

#define LOG_INFO(...)	SPDLOG_INFO(__VA_ARGS__)
#define LOG_WARN(...)	SPDLOG_WARN(__VA_ARGS__)
#define LOG_ERROR(...)	SPDLOG_ERROR(__VA_ARGS__)

#ifdef assert
#undef assert
#endif

#if GUEEPO2D_MACOS // todo: figure out how __debugbreak on os x
#define	   assert(x, ...) { if(!(x)) { LOG_ERROR(__VA_ARGS__); } }
#define g2dassert(x, ...) { if(!(x)) { LOG_ERROR(__VA_ARGS__); } }
#else
#define	   assert(x, ...) { if(!(x)) { LOG_ERROR(__VA_ARGS__); __debugbreak(); } }
#define g2dassert(x, ...) { if(!(x)) { LOG_ERROR(__VA_ARGS__); __debugbreak(); } }
#endif