cmake_minimum_required(VERSION 3.10)

project(MyProject C)

set(CMAKE_PREFIX_PATH "C:/nes-emu/lib/sdl")

find_package(SDL3 REQUIRED CONFIG)


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
    src/cli.c
    src/ppu.c
    src/boot.c
    src/framebuffero.c
    src/interrupt.c
    src/nes_cycle.c
    src/oam_dma.c
)

add_executable(my_app ${SOURCES})

target_compile_definitions(my_app PRIVATE _CRT_SECURE_NO_WARNINGS)
target_include_directories(my_app PRIVATE inc)

target_link_libraries(my_app PRIVATE SDL3::SDL3-static)

