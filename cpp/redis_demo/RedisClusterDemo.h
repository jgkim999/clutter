#pragma once
#include <sw/redis++/redis_cluster.h>

class RedisClusterDemo
{
public:
    RedisClusterDemo() = default;
    ~RedisClusterDemo() = default;

    static void String(std::shared_ptr<sw::redis::RedisCluster> redis);
    static void List(std::shared_ptr<sw::redis::RedisCluster> redis);
    static void Hash(std::shared_ptr<sw::redis::RedisCluster> redis);
    static void Set(std::shared_ptr<sw::redis::RedisCluster> redis);
    static void SortedSet(std::shared_ptr<sw::redis::RedisCluster> redis);
    static void Pipeline(std::shared_ptr<sw::redis::RedisCluster> redis);
};
