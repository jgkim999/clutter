#include "RedisClusterManager.h"

RedisClusterManager::RedisClusterManager(const std::string& ip, int port, int pool_size)
{
    sw::redis::ConnectionOptions connection_options;
    connection_options.host = ip;
    connection_options.port = port;

    sw::redis::ConnectionPoolOptions pool_options;
    pool_options.size = pool_size;

    write_redis_ = std::make_shared<sw::redis::RedisCluster>(
        connection_options,
        pool_options,
        sw::redis::Role::MASTER);

    read_redis_ = std::make_shared<sw::redis::RedisCluster>(
        connection_options,
        pool_options,
        sw::redis::Role::SLAVE);
}
