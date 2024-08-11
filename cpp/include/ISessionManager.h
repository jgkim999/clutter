#ifndef _ISESSION_MANAGER_
#define _ISESSION_MANAGER_

#include <boost/asio.hpp>

class ISessionManager {
public:
  ISessionManager() {}
  virtual ~ISessionManager() {}
  virtual int count() = 0;
  virtual void connected(boost::asio::ip::tcp::socket socket) = 0;
  virtual void closed(long long sessionNum_) = 0;
};

#endif // _ISESSION_MANAGER_
