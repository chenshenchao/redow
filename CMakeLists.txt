cmake_minimum_required(VERSION 3.24)

include("cmake/Redis.cmake")

if (NOT WIN32)
	message(FATAL_ERROR "must Windows.")
endif()

if (MSVC)
    # 静态链接 MT
    option(VS_LINK_STATIC_MT "static link MT." ON)
endif()

project(redow LANGUAGES CXX)

set(REDIS_INSTALL_DIR "${PROJECT_SOURCE_DIR}")
BuildRedisOnWindows(${REDIS_INSTALL_DIR})

add_subdirectory(redow)
