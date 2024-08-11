#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "../include/session.h"
#include "../include/server.h"
#include "../include/SessionManager.h"
#include "../libs/spdlog/include/spdlog/spdlog.h"
#include <fmt/core.h>
#include <nlohmann/json.hpp>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> logger;

void initLog()
{
  try
  {
    std::filesystem::path cwd = std::filesystem::current_path();
    if (std::filesystem::exists(cwd.string() + "/logs") == false)
    {
      std::filesystem::create_directory(cwd.string() + "logs");
    }

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(cwd.string() + "/logs/multisink.txt", true);
    file_sink->set_pattern("[%H:%M:%S %z] [source %s] [function %!] [line %#] %v");
    file_sink->set_level(spdlog::level::trace);

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_pattern("[%H:%M:%S %z] [source %s] [function %!] [line %#] %v");
    console_sink->set_level(spdlog::level::trace);

    auto multiLogger = new spdlog::logger("multi_sink", {file_sink, console_sink});
    logger.reset(multiLogger);
    spdlog::set_default_logger(logger);
    spdlog::flush_on(spdlog::level::info);
  }
  catch (const spdlog::spdlog_ex &ex)
  {
    std::cout << "Log init failed: " << ex.what() << std::endl;
  }
}

int main(int argc, char* argv[])
{
  initLog();

  const std::string optionFileName("config.json");
  std::filesystem::path cwd = std::filesystem::current_path();
  std::ifstream optionFile(cwd.string() + "/" + optionFileName);
  if (optionFile.good() == false)
  {
    SPDLOG_ERROR("Read error:{}", optionFileName);
    return -1;
  }
  nlohmann::json optionJson = nlohmann::json::parse(optionFile);
  SPDLOG_INFO(optionJson.dump());

  std::string s = fmt::format("The answer is {}.", 42);
  SPDLOG_INFO("Welcome to spdlog!");
  SPDLOG_ERROR("Some error message with arg: {}", 1);

  SPDLOG_WARN("Easy padding in numbers like {:08d}", 12);
  SPDLOG_CRITICAL("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  SPDLOG_INFO("Support for floats {:03.2f}", 1.23456);
  SPDLOG_INFO("Positional args are {1} {0}..", "too", "supported");
  SPDLOG_INFO("{:<30}", "left aligned");

  //logger->set_level(spdlog::level::debug); // Set global log level to debug
  logger->debug("This message should be displayed..");

  // change log pattern
  //logger->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

  // Compile time log levels
  // define SPDLOG_ACTIVE_LEVEL to desired level
  SPDLOG_TRACE("Some trace message with param {}", 42);
  SPDLOG_DEBUG("Some debug message");

  try
  {
    /*
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }
    */
    auto sessionManager = new SessionManager();

    boost::asio::io_context io_context;
    auto server = new Server(io_context, optionJson["port"], sessionManager);

    io_context.run();

    delete server;
    delete sessionManager;
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
