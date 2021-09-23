#include <gueepo2d.h>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

int main(void) {
	gueepo::Log::Initialize();
	LOG_INFO("Logger Initialized!");
	LOG_WARN("Logger Initialized!");
	LOG_ERROR("Logger Initialized!");
}