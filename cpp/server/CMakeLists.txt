cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(FOO_PROJECT_NAME
        Foo
)
set(FOO_SOURCE_DIR
        src
)
set(FOO_LIBRARIES_DIR
        libs
)
set(FOO_LIBRARIES
        spdlog
        fmt
)
set(FOO_SOURCE
        ${FOO_SOURCE_DIR}/main.cpp
        src/SessionManager.cpp
        src/server.cpp
        src/session.cpp
)

project(${FOO_PROJECT_NAME} C CXX)
###########
# Project #
###########
add_subdirectory(./include)
add_subdirectory(./src)
add_executable(${FOO_PROJECT_NAME} ${FOO_SOURCE})

foreach(LIBRARY ${FOO_LIBRARIES})
    add_subdirectory("${FOO_LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)
target_link_libraries(${FOO_PROJECT_NAME} ${FOO_LIBRARIES})

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(libs/json)
target_link_libraries(${FOO_PROJECT_NAME} nlohmann_json::nlohmann_json)

#configure_file(config.json config.json COPYONLY)
file(COPY config.json DESTINATION ${CMAKE_BINARY_DIR})
