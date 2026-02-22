cmake_minimum_required(VERSION 3.10)

project(MyProject C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCES
    src/main.c
    src/cpu.c
    src/6502_mem.c
    src/cpu_decoder.c
    src/addrmode.c
    src/decode_lut.c
    src/opcode_handle.c
)

add_executable(my_app ${SOURCES})

target_include_directories(my_app PRIVATE inc)
