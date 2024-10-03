#include <spdlog/spdlog.h>
#include <sw/redis++/redis++.h>
#include "AppLogger.h"
#include "RedisDemo.h"

int main()
{
	AppLogger appLogger;
        
	spdlog::info("Start app");

    sw::redis::Redis redis = sw::redis::Redis("tcp://192.168.0.47:6379");

    sw::redis::RedisCluster redis_cluster = sw::redis::RedisCluster("tcp://127.0.0.1:7000");

    RedisDemo::String(redis);
    RedisDemo::List(redis);
    RedisDemo::Hash(redis);
    RedisDemo::Set(redis);
    RedisDemo::SortedSet(redis);
    RedisDemo::Pipeline(redis);
    
	return 0;
}
