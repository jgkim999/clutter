cmake_minimum_required(VERSION 3.10)

project(RedisDemo)

find_package(fmt CONFIG REQUIRED)
find_package(redis++ CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(RedisDemo RedisDemo.cpp)

target_link_libraries(RedisDemo PRIVATE fmt::fmt)
target_link_libraries(RedisDemo PRIVATE redis++::redis++)
target_link_libraries(RedisDemo PRIVATE spdlog::spdlog)
