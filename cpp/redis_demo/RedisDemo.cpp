#include "RedisDemo.h"

#include <iostream>
#include <unordered_set>
#include <spdlog/spdlog.h>
#include <sw/redis++/pipeline.h>
#include <sw/redis++/queued_redis.h>

void RedisDemo::String(sw::redis::Redis& redis)
{
    spdlog::info("String ----------------------");
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

void RedisDemo::List(sw::redis::Redis& redis)
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

void RedisDemo::Hash(sw::redis::Redis& redis)
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

void RedisDemo::Set(sw::redis::Redis& redis)
{
    spdlog::info("Set ---------------------");
    std::string setKey = "set";
    std::unordered_set<std::string> set = { "m1", "m2", "m3" };
    redis.sadd(setKey, set.begin(), set.end());
    redis.expire(setKey, std::chrono::minutes(1));

    // std::initializer_list to Redis SET.
    redis.sadd(setKey, { "m4", "m5" });
        
    // Redis SET to std::unordered_set<std::string>.
    std::unordered_set<std::string> s;
    redis.smembers(setKey, std::inserter(s, s.begin()));

    const char* const delim = ", ";
    std::ostringstream imploded;
    std::copy(
        s.begin(),
        s.end(),
        std::ostream_iterator<std::string>(imploded, delim));
    spdlog::info("set size:{} value:{}", s.size(), imploded.str());

    if (redis.sismember(setKey, "m1"))
    {
        spdlog::info("set {0} member:{1} exist", setKey, "m1");
    }
}

void RedisDemo::SortedSet(sw::redis::Redis& redis)
{
    spdlog::info("SortedSet ---------------------");
    std::string sortedSetKey = "sorted_set";
    std::unordered_map<std::string, double> scores = {
        {"m1", 1.0},
        {"m2", 1.5},
        {"m3", 2.0},
        {"m4", 2.5},
        {"m5", 3.0},
        {"m6", 3.5},
        {"m7", 4.0},
        {"m8", 4.5},
        {"m9", 5.0}
    };
    redis.zadd(sortedSetKey, scores.begin(), scores.end());
    redis.expire(sortedSetKey, std::chrono::minutes(1));

    // Redis SORTED SET to std::vector<std::pair<std::string, double>>.
    // NOTE: The return results of zrangebyscore are ordered, if you save the results
    // in to `std::unordered_map<std::string, double>`, you'll lose the order.
    std::vector<std::pair<std::string, double>> zset_result;
    redis.zrangebyscore(
        sortedSetKey,
        sw::redis::UnboundedInterval<double>{},            // (-inf, +inf)
        std::back_inserter(zset_result));

    for (const auto& member : zset_result)
    {
        spdlog::info("{0}:{1}", member.first, member.second);
    }
    
    std::vector<std::string> without_score;
    redis.zrangebyscore(
        sortedSetKey,
        sw::redis::BoundedInterval<double>(1.5, 3.4, sw::redis::BoundType::CLOSED),   // [1.5, 3.4]
        std::back_inserter(without_score));
    for (const auto& member : without_score)
    {
        spdlog::info("{0}", member);
    }

    std::vector<std::pair<std::string, double>> with_score;
    redis.zrangebyscore(
        sortedSetKey,
        sw::redis::BoundedInterval<double>(1.5, 3.4, sw::redis::BoundType::LEFT_OPEN),    // (1.5, 3.4]
        std::back_inserter(with_score));
    for (const auto& member : with_score)
    {
        spdlog::info("{0} {1}", member.first, member.second);
    }
}

void RedisDemo::Pipeline(sw::redis::Redis& redis)
{
    spdlog::info("Pipeline ---------------------");
    sw::redis::Pipeline pipe = redis.pipeline();
    auto pipe_replies = pipe.set("key", "value")
        .get("key")
        .rename("key", "new-key")
        .rpush("list_pipeline", { "a", "b", "c" })
        .lrange("list_pipeline", 0, -1)
        .exec();

    auto set_cmd_result = pipe_replies.get<bool>(0);
    spdlog::info("set_cmd_result:{}", set_cmd_result);

    auto get_cmd_result = pipe_replies.get<sw::redis::OptionalString>(1);
    if (get_cmd_result)
    {
        spdlog::info("get_cmd_result:{}", get_cmd_result.value());
    }

    // rename command result
    pipe_replies.get<void>(2);

    auto rpush_cmd_result = pipe_replies.get<long long>(3);
    spdlog::info("rpush_cmd_result:{}", rpush_cmd_result);

    std::vector<std::string> lrange_cmd_result;
    pipe_replies.get(4, back_inserter(lrange_cmd_result));
    for (const auto& val : lrange_cmd_result)
    {
        spdlog::info("lrange_cmd_result:{}", val);
    }
}
