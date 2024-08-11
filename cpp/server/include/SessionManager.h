#ifndef _SESSION_MANAGER_
#define _SESSION_MANAGER_

#include "./ISessionManager.h"
#include <atomic>
#include <shared_mutex>
#include <map>

class ISession;

class SessionManager : public ISessionManager {
public:
  SessionManager();
  ~SessionManager();
  virtual int count();
  virtual void connected(boost::asio::ip::tcp::socket socket);
  virtual void closed(long long sessionNum);
private:
  std::shared_mutex mutex_;
  std::atomic<long long> sessionNum_;
  std::map<long long, std::shared_ptr<ISession>> sessions_;
};

#endif // _SESSION_MANAGER_
