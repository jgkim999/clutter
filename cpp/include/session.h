#ifndef _SESSION_
#define _SESSION_

#include <memory>
#include <boost/asio.hpp>
#include "ISession.h"

class ISessionManager;

class Session
  : public std::enable_shared_from_this<Session>
  , public ISession
{
public:
  Session(
    boost::asio::ip::tcp::socket socket,
    ISessionManager* sessionManager,
    long long sessionNum);
  ~Session();
  virtual void start();
  virtual void stop();
private:
  void do_read();
  void do_write(std::size_t length);
private:
  ISessionManager* sessionManager_;
  long long sessionNum_;
  boost::asio::ip::tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};

#endif // _SESSION_
