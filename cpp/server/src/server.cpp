#include "../include/server.h"
#include "../include/session.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io_context, short port, ISessionManager* sessionManager)
  : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
  sessionManager_ = sessionManager;
  do_accept();
}

void Server::do_accept()
{
  acceptor_.async_accept(
    [this](boost::system::error_code ec, tcp::socket socket)
    {
      if (!ec)
      {
        sessionManager_->connected(std::move(socket));
        //std::make_shared<session>(std::move(socket))->start();
      }
      do_accept();
    }
  );
}
