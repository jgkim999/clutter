#include <spdlog/spdlog.h>
#include <sw/redis++/redis++.h>
#include "AppLogger.h"

int main()
{
	AppLogger appLogger;
        
	spdlog::info("Start app");

	auto redis = sw::redis::Redis("tcp://192.168.0.47:6379");

    // ***** SET commands *****
    {
        spdlog::info("Set ----------------------");
        redis.set("key1", "val1", std::chrono::minutes(1));
        auto val = redis.get("key1");    // val is of type OptionalString. See 'API Reference' section for details.
        if (val)
        {
            spdlog::info(val.value());
        }
        else
        {
            spdlog::error("Failed to get value from redis");
        }
		// utf8 support
        redis.set(u8"키2", u8"값2", std::chrono::minutes(1));
    }
    // ***** LIST commands *****
    {
        spdlog::info("List ---------------------");
        std::string listKey = "list";
        std::vector<std::string> vec = { "a", "b", "c" };
        redis.rpush(listKey, vec.begin(), vec.end());
        redis.expire(listKey, std::chrono::minutes(1));

        // std::initializer_list to Redis LIST.
        redis.rpush(listKey, { "a", "b", "c" });

        // Redis LIST to std::vector<std::string>.
        vec.clear();
        redis.lrange(listKey, 0, -1, std::back_inserter(vec));

        const char* const delim = ", ";
        std::ostringstream imploded;
        std::copy(
            vec.begin(),
            vec.end(),
            std::ostream_iterator<std::string>(imploded, delim));
        spdlog::info("list size:{} value:{}", vec.size(), imploded.str());
    }
    // ***** HASH commands *****
    {
        spdlog::info("Hash ---------------------");
		std::string hashKey = "hash";
        redis.hset(hashKey, "field1", "val1");
        redis.expire(hashKey, std::chrono::minutes(1));

        // Another way to do the same job.
        redis.hset(hashKey, std::make_pair("field2", "val2"));

        // std::unordered_map<std::string, std::string> to Redis HASH.
        std::unordered_map<std::string, std::string> m = {
            {"field3", "val3"},
            {"field4", "val4"}
        };
        redis.hmset(hashKey, m.begin(), m.end());

        // Redis HASH to std::unordered_map<std::string, std::string>.
        m.clear();
        redis.hgetall(hashKey, std::inserter(m, m.begin()));
       
        spdlog::info("{} size:{}", hashKey, m.size());
		for (const auto& keyValue : m)
		{
			spdlog::info("{0}:{1}", keyValue.first, keyValue.second);
		}

        // Get value only.
        // NOTE: since field might NOT exist, so we need to parse it to OptionalString.
        std::vector<sw::redis::OptionalString> vals;
        redis.hmget(hashKey, { "field1", "field2", "field3", "field4" }, std::back_inserter(vals));
		for (const auto& val : vals)
		{
            spdlog::info("val:{0}", val.value());
		}
    }
	return 0;
}
