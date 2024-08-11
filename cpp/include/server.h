#ifndef _X_SERVER_H_
#define _X_SERVER_H_

#include <boost/asio.hpp>
#include "ISessionManager.h"

class Server
{
public:
  Server(boost::asio::io_context& io_context, short port, ISessionManager* sessionManager);
private:
  void do_accept();
private:
  boost::asio::ip::tcp::acceptor acceptor_;
  ISessionManager* sessionManager_;
};

#endif // _X_SERVER_H_
