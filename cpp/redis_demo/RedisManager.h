#pragma once

#include <sw/redis++/redis.h>
#include <string_view>
#include "crc.h"
#include "RedisOption.h"

class RedisManager
{
public:
    RedisManager(const std::vector<redis_demo::Option>& options);
    RedisManager(const RedisManager& rhs) = delete;
    ~RedisManager() = default;
    RedisManager& operator=(const RedisManager& rhs) = delete;

    std::shared_ptr<sw::redis::Redis> getConnection(const std::string_view& key);
private:
    std::unique_ptr<redis_demo::CRC16_ARC> crc_;
    std::vector<std::shared_ptr<sw::redis::Redis>> redis_;
};
