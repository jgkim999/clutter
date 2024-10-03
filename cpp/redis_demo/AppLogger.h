#pragma once

#include <spdlog/logger.h>

class AppLogger
{
public:
	AppLogger();
	~AppLogger();
private:
	std::shared_ptr<spdlog::logger> logger_;
};
