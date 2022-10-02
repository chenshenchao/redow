cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)

project(redow LANGUAGES CXX)

if (MSVC)
    # 静态链接 MT
    option(VS_LINK_STATIC_MT "static link mt." OFF)

    if (VS_LINK_STATIC_MT)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()

    # 定义 UNICODE 宏，使用 UNICODE
    add_definitions("-DUNICODE" "-D_UNICODE")
endif()

add_executable(redow)

target_sources(
    redow
    PRIVATE
    "src/main.cpp"
    "src/redow.h"
    "src/redow.cpp"
 "src/redis.h" "src/redis.cpp")

target_link_libraries(
    redow
    Shlwapi.lib
    ws2_32.lib
)