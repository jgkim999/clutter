#pragma once
#include "RedisManager.h"

class RedisDemo
{
public:
    RedisDemo() = default;
    ~RedisDemo() = default;
    static void String(RedisManager& redisManager);
    /*
    static void List(RedisManager& redisManager);
    static void Hash(RedisManager& redisManager);
    static void Set(RedisManager& redisManager);
    static void SortedSet(RedisManager& redisManager);
    static void Pipeline(RedisManager& redisManager);
    */
};
