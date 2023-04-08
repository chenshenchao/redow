cmake_minimum_required(VERSION 3.23)

project(redow LANGUAGES CXX)

if (MSVC)
    # 静态链接 MT
    option(VS_LINK_STATIC_MT "static link MT." ON)
endif()

add_subdirectory(redow)
