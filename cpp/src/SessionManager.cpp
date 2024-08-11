#include "../include/SessionManager.h"
#include "../include/session.h"
#include "../include/SessionManager.h"

SessionManager::SessionManager()
  : sessionNum_(0) {
}

SessionManager::~SessionManager() {
}

int SessionManager::count()
{
  std::shared_lock<std::shared_mutex> lock(mutex_);
  return static_cast<int>(sessions_.size());
}

void SessionManager::connected(boost::asio::ip::tcp::socket socket) {

  ++sessionNum_;
  auto session = std::make_shared<Session>(
    std::move(socket),
    this,
    sessionNum_);
  std::unique_lock<std::shared_mutex> lock(mutex_);
  sessions_.insert({sessionNum_, session});
  session->start();
}

void SessionManager::closed(long long sessionNum) {
  std::unique_lock<std::shared_mutex> lock(mutex_);
  auto iter = sessions_.find(sessionNum);
  if (iter != sessions_.end()) {
    auto session = iter->second;
    session->stop();
    sessions_.erase(iter);
  }
}
