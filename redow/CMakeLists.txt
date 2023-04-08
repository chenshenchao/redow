add_executable(redow)

set_target_properties(
	redow
	PROPERTIES
	CXX_STANDARD_REQUIRED ON
	CXX_STANDARD 20
)

if (VS_LINK_STATIC_MT)
	set_target_properties(
		redow
		PROPERTIES
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
	)
endif()

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
