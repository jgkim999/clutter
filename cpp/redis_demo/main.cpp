#include <spdlog/spdlog.h>

#include "AppLogger.h"
#include "RedisClusterDemo.h"
#include "RedisClusterManager.h"
#include "RedisDemo.h"
#include "RedisManager.h"
#include "RedisOption.h"

int main()
{
	AppLogger appLogger;
        
	spdlog::info("Start app");
    {
        std::vector<redis_demo::Option> redisUris =
        {
            {"192.168.0.47", 6390, 3},
            {"192.168.0.47", 6391, 3}
        };

        RedisManager redisManager(redisUris);

        size_t loop = 100;
        for (size_t i = 0; i < loop; ++i)
        {
            std::string key = "RedisManagerKey" + std::to_string(i);
            std::string value = "value" + std::to_string(i);
            redisManager.getConnection(key)->set(key, value, std::chrono::minutes(10));
            spdlog::info("Set key:{} value:{}", key, value);
        }
        for (size_t i = 0; i < loop; ++i)
        {
            std::string key = "RedisManagerKey" + std::to_string(i);
            auto value = redisManager.getConnection(key)->get(key);
            if (value)
            {
                spdlog::info("Get key:{} value:{}", key, value.value());
            }
            else
            {
                spdlog::error("Failed to getConnection value from redis");
            }
        }
    }
    /*
    RedisDemo::List(redis);
    RedisDemo::Hash(redis);
    RedisDemo::Set(redis);
    RedisDemo::SortedSet(redis);
    RedisDemo::Pipeline(redis);
    */
    {
        RedisClusterManager redisCluster("192.168.0.47", 6381, 3);

        RedisClusterDemo::String(redisCluster.get_write());
        RedisClusterDemo::List(redisCluster.get_write());
        RedisClusterDemo::Hash(redisCluster.get_write());
        RedisClusterDemo::Set(redisCluster.get_write());
        RedisClusterDemo::SortedSet(redisCluster.get_write());
        RedisClusterDemo::Pipeline(redisCluster.get_write());

        size_t loop = 100;
        for (size_t i = 0; i < loop; ++i)
        {
            std::string key = "key" + std::to_string(i);
            std::string value = "value" + std::to_string(i);
            redisCluster.get_write()->set(key, value, std::chrono::minutes(10));
            spdlog::info("Master Set key:{} value:{}", key, value);
        }

        for (size_t i = 0; i < loop; ++i)
        {
            try
            {
                std::string key = "key" + std::to_string(i);
                auto val = redisCluster.get_read()->get(key);
                if (val)
                {
                    spdlog::info("Slave Get key:{} value:{}", key, val.value());
                }
                else
                {
                    spdlog::error("Failed to getConnection value from redis");
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            catch (const sw::redis::ReplyError& e)
            {
                spdlog::error("Exception:{}", e.what());
            }
            catch (const sw::redis::IoError& e)
            {
                spdlog::error("Exception:{}", e.what());
            }
            catch (const sw::redis::Error& e)
            {
                spdlog::error("Exception:{}", e.what());
            }
            catch (...) // catch any exception
            {
                spdlog::error("Unknown exception");
            }
        }
    }
    spdlog::info("End app");
	return 0;
}
