#pragma once
#include <string>

namespace redis_demo
{
    struct Option
    {
        std::string address;
        int port;
        int pool_size;
    };
}
