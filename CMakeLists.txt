 
project (TinyLoomScript)

# Set minimum version
cmake_minimum_required (VERSION 2.8.6)

include_directories( 
    ${CMAKE_CURRENT_SOURCE_DIR}
    loom/vendor/jansson
    loom/vendor/lua/src
    loom/vendor/seatest
)

#jansson
file (GLOB JANSSON_SRC loom/vendor/jansson/src/*.c)

#lua (we'll add LuaJIT later)
file (GLOB LUA_SRC loom/vendor/lua/src/*.c)

#seatest (we'll add LuaJIT later)
set (SEATEST_SRC loom/vendor/seatest/seatest.c)

# common files
file (GLOB COMMON_SRC 
    loom/common/xml/*.cpp 
    loom/common/utils/*.cpp 
    loom/common/core/*.cpp 
    loom/common/core/*.c 
    loom/common/platform/*.cpp 
    loom/common/platform/*.c )

if (APPLE)
    set (COMMON_SRC ${COMMON_SRC} loom/common/platform/platformFileIOS.m)        
endif(APPLE)

add_library(TinyLoomScript ${JANSSON_SRC} ${LUA_SRC} ${SEATEST_SRC} ${COMMON_SRC})

