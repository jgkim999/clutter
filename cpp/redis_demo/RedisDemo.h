#pragma once
#include <sw/redis++/redis.h>

class RedisDemo
{
public:
    RedisDemo() = default;
    ~RedisDemo() = default;
    static void String(sw::redis::Redis& redis);
    static void List(sw::redis::Redis& redis);
    static void Hash(sw::redis::Redis& redis);
    static void Set(sw::redis::Redis& redis);
    static void SortedSet(sw::redis::Redis& redis);
    static void Pipeline(sw::redis::Redis& redis);
};
