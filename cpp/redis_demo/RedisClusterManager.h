#pragma once

#include <sw/redis++/redis_cluster.h>

class RedisClusterManager
{
public:
    RedisClusterManager(const std::string& ip, int port, int pool_size);
    RedisClusterManager(const RedisClusterManager& rhs) = delete;
    ~RedisClusterManager() = default;    
    RedisClusterManager& operator=(const RedisClusterManager& rhs) = delete;

    std::shared_ptr<sw::redis::RedisCluster> get_write() { return write_redis_; }
    std::shared_ptr<sw::redis::RedisCluster> get_read() { return read_redis_; }

private:
    std::shared_ptr<sw::redis::RedisCluster> write_redis_;
    std::shared_ptr < sw::redis::RedisCluster> read_redis_;
};
