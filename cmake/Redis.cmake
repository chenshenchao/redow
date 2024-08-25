include(ExternalProject)

set(REDIS_GIT_REPOSITORY "git@github.com:redis/redis.git" CACHE STRING "redis git link.")
set(REDIS_GIT_TAG "7.0.14" CACHE STRING "redis git tag.")


find_program(MSYS2_SHELL NAMES msys2_shell.cmd msys2_shell)
message(STATUS "msys2_shell: ${MSYS2_SHELL}")
get_filename_component(MSYS2_DIR ${MSYS2_SHELL} DIRECTORY)
message(STATUS "msys2: ${MSYS2_DIR}")
set(MSYS2_DLL_PATH "${MSYS2_DIR}/usr/bin/msys-2.0.dll")
message(STATUS "msys2 dll: ${MSYS2_DLL_PATH}")

# ExternalProject 的方式编译 redis
function(
    BuildRedisOnWindows
    REDIS_INSTALL_DIR
)
    add_custom_target(redis)

    set(REDIS_SOURCE_DIR "${PROJECT_BINARY_DIR}/redis_bin-prefix/src/redis_bin")

    # 编译 redis
    ExternalProject_Add(
        redis_bin
        GIT_REPOSITORY ${REDIS_GIT_REPOSITORY}
        GIT_TAG ${REDIS_GIT_TAG}
        GIT_SHALLOW ON
        GIT_PROGRESS ON

        CONFIGURE_COMMAND ""
        BUILD_COMMAND ${MSYS2_SHELL} -no-start -defterm -mingw64 -where ${REDIS_SOURCE_DIR} -shell bash -c "make CFLAGS='-D__GNU_VISIBLE -w' PREFIX=${REDIS_INSTALL_DIR} install"
        INSTALL_COMMAND ""

        STEP_TARGETS build
        EXCLUDE_FROM_ALL TRUE
    )

    # 复制 msys-2.0.dll
    add_custom_command(
        TARGET
        redis_bin
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${MSYS2_DLL_PATH} "${REDIS_INSTALL_DIR}/bin"
    )

    add_dependencies(redis redis_bin)
endfunction()

include(FetchContent)

# TODO FetchContent 方式编译 redis
function(
    FetchRedis
)
    # 编译 redis
    FetchContent_Declare(
        redis_bin
        GIT_REPOSITORY ${REDIS_GIT_REPOSITORY}
        GIT_TAG ${REDIS_GIT_TAG}
        GIT_SHALLOW ON # 浅克隆，git 参数加 --depth=1
        GIT_PROGRESS ON # 打印下载进度
    )
    FetchContent_GetProperties(redis_bin)
    if(NOT redis_bin_POPULATED)
        FetchContent_Populate(redis_bin)
        message(STATUS "[redis_bin]: ${redis_bin_SOURCE_DIR}")
    endif()
endfunction()
