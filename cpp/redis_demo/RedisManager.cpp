#include "RedisManager.h"

RedisManager::RedisManager(const std::vector<redis_demo::Option>& options)
{
    // CRC16 use look up table
    crc_ = std::make_unique<redis_demo::CRC16_ARC>(true);

    for (const auto& option : options)
    {
        sw::redis::ConnectionOptions connection_options;
        connection_options.type = sw::redis::ConnectionType::TCP;
        connection_options.host = option.address;
        connection_options.port = option.port;
        connection_options.keep_alive = true;
        connection_options.keep_alive_s = std::chrono::seconds(5);

        sw::redis::ConnectionPoolOptions pool_options;
        pool_options.size = option.pool_size;
        pool_options.wait_timeout = std::chrono::milliseconds(0);
        pool_options.connection_lifetime = std::chrono::milliseconds(0);
        pool_options.connection_idle_time = std::chrono::milliseconds(0);

        auto redis = std::make_shared<sw::redis::Redis>(connection_options, pool_options);
        redis_.push_back(redis);
    }
}

std::shared_ptr<sw::redis::Redis> RedisManager::getConnection(const std::string_view& key)
{
    uint16_t crcResult = crc_->calculate(
       reinterpret_cast<const uint8_t*>(key.data()),
       static_cast<int>(key.length()));
    if (redis_.empty())
    {
        return nullptr;
    }
    crcResult = crcResult % redis_.size();
    return redis_[crcResult];
}
