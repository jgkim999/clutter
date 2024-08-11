#include "../include/session.h"
#include "../include/SessionManager.h"
#include <iostream>
#include <spdlog/spdlog.h>

Session::Session(
  boost::asio::ip::tcp::socket socket,
  ISessionManager* sessionManager,
  long long sessionNum)
  : socket_(std::move(socket))
  , sessionNum_(sessionNum)
  , sessionManager_(sessionManager)
{
  SPDLOG_INFO("Session created");
}

Session::~Session()
{
  std::cout << "Session removed" << std::endl;
}

void Session::start()
{
  std::cout << "Session start" << std::endl;
  do_read();
}

void Session::stop() {
}

void Session::do_read()
{
  auto self(shared_from_this());
  socket_.async_read_some(boost::asio::buffer(data_, max_length),
    [this, self](boost::system::error_code ec, std::size_t length)
    {
      if (!ec)
      {
        std::cout << "read:" << length << "bytes" << std::endl;
        do_write(length);
      }
      else
      {
        sessionManager_->closed(sessionNum_);
      }
    });
}

void Session::do_write(std::size_t length)
{
  auto self(shared_from_this());
  boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
      [this, self](boost::system::error_code ec, std::size_t /*length*/)
      {
        if (!ec)
        {
          do_read();
        }
      });
}
