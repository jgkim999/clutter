cmake_minimum_required(VERSION 3.10)

project(RedisDemo)

find_package(fmt)
find_package(redis++)
find_package(spdlog)

add_executable(
    RedisDemo
    main.cpp
    AppLogger.cpp
    RedisDemo.cpp)

target_link_libraries(RedisDemo PRIVATE fmt::fmt)
target_link_libraries(RedisDemo PRIVATE redis++::redis++)
target_link_libraries(RedisDemo PRIVATE spdlog::spdlog)
