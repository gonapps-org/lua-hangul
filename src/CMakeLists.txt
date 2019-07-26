find_library(lua_LIBRARIES NAMES liblua5.3.so liblua-5.3.so liblua-5.3.so.0 liblua.a REQUIRED)
find_path(lua_INCLUDE_DIRS NAMES lua.h lualib.h lauxlib.h PATHS /usr/include/lua5.3 REQUIRED)
find_library(hangul_LIBRARIES NAMES libhangul.so libhangul.so.1 libhangul.so.1.0.0 REQUIRED)
find_path(hangul_INCLUDE_DIRS NAMES hangul.h PATHS /usr/include/hangul-1.0 REQUIRED)

add_library(lua_hangul SHARED)
target_sources(lua_hangul PRIVATE lua_hangul.c)
target_compile_options(lua_hangul PRIVATE -Wall)
list(APPEND public_headers "lua_hangul.h")

set_target_properties(
    lua_hangul
    PROPERTIES
    C_STANDARD 11
    PUBLIC_HEADER "${public_headers}"
)

target_include_directories(
    lua_hangul
    PRIVATE
    ${lua_INCLUDE_DIRS}
    ${hangul_INCLUDE_DIRS}
)

target_link_libraries(
    lua_hangul
    ${lua_LIBRARIES}
    ${hangul_LIBRARIES}
)
