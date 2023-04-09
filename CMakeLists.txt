cmake_minimum_required(VERSION 3.23)

if (NOT WIN32)
	message(FATAL_ERROR "must Windows.")
endif()

project(redow LANGUAGES CXX)

if (MSVC)
    # 静态链接 MT
    option(VS_LINK_STATIC_MT "static link MT." ON)
endif()

add_subdirectory(redow)
