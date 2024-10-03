#include "AppLogger.h"

#include <chrono>
#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

AppLogger::AppLogger()
{
    spdlog::init_thread_pool(8192, 1);
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
    auto max_size = 1048576 * 5;
    auto max_files = 3;
    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/app_log.txt", max_size, max_files);
    std::vector<spdlog::sink_ptr> sinks{ stdout_sink, rotating_sink };
    logger_ = std::make_shared<spdlog::async_logger>(
        "logger",
        sinks.begin(),
        sinks.end(),
        spdlog::thread_pool(),
        spdlog::async_overflow_policy::block);
    spdlog::set_default_logger(logger_);
    // Set global log level to debug
    spdlog::set_level(spdlog::level::debug);
    spdlog::flush_every(std::chrono::seconds(3));
    // change log pattern
    //spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    /*
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);
    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");
	*/
}

AppLogger::~AppLogger()
{
}
