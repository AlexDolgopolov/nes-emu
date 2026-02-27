cmake_minimum_required(VERSION 3.10)

project(nes-test C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCES
    src/main.c
)

add_executable(nes-emu-test ${SOURCES})

target_include_directories(nes-emu-test PRIVATE inc)

add_library(cjson STATIC IMPORTED)

set_property(TARGET cjson PROPERTY IMPORTED_LOCATION "../cJson/build/libcjson.a")

target_link_libraries(nes-emu-test PRIVATE cjson)

target_include_directories(nes-emu-test PRIVATE cJson)
