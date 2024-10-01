#include <iostream>
#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/async.h>

int main()
{
    spdlog::init_thread_pool(8192, 1);
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
    auto max_size = 1048576 * 5;
    auto max_files = 3;
    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/rotating.txt", max_size, max_files);
    std::vector<spdlog::sink_ptr> sinks{ stdout_sink, rotating_sink };
    auto logger = std::make_shared<spdlog::async_logger>(
        "logger",
        sinks.begin(),
        sinks.end(),
        spdlog::thread_pool(),
        spdlog::async_overflow_policy::block);
    spdlog::set_default_logger(logger);
    spdlog::flush_every(std::chrono::seconds(3));

    //std::cout << "Hello World!\n";
    //fmt::print("Hello World!\n");

    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);
    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    //spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    //spdlog::debug("This message should be displayed..");

    // change log pattern
    //spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    // Compile time log levels
    // Note that this does not change the current log level, it will only
    // remove (depending on SPDLOG_ACTIVE_LEVEL) the call on the release code.
    //SPDLOG_TRACE("Some trace message with param {}", 42);
    //SPDLOG_DEBUG("Some debug message");
	return 0;
}
