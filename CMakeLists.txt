cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

project(redow LANGUAGES CXX)

if (MSVC)
    # 静态链接 MT
    option(VS_LINK_STATIC_MT "static link mt." ON)

    if (VS_LINK_STATIC_MT)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()
endif()

add_executable(redow)

# 定义 UNICODE 宏，使用 UNICODE
target_compile_definitions(
    redow
    PRIVATE
    "-DUNICODE"
    "-D_UNICODE"
)

target_sources(
    redow
    PRIVATE
    "src/main.cpp"
    "src/redow.h"
    "src/redow.cpp"
    "src/redis.h"
    "src/redis.cpp"
)

target_link_libraries(
    redow
    Shlwapi.lib
    ws2_32.lib
)