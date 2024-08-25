cmake_minimum_required(VERSION 3.24)

set(ENV_HTTP_PROXY "" CACHE STRING "set env HTTP_PROXY.")
set(ENV_HTTPS_PROXY "" CACHE STRING "set env HTTPS_PROXY.")

if (NOT ${ENV_HTTP_PROXY} STREQUAL "")
    message(STATUS "set http proxy: ${ENV_HTTP_PROXY}")
    set(ENV{HTTP_PROXY} ${ENV_HTTP_PROXY})
endif()


if (NOT ${ENV_HTTPS_PROXY} STREQUAL "")
    message(STATUS "set https proxy: ${ENV_HTTPS_PROXY}")
    set(ENV{HTTPS_PROXY} ${ENV_HTTPS_PROXY})
endif()


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
