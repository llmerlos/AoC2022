cmake_minimum_required(VERSION 3.24)
project(AoC2022 C)

set(CMAKE_C_STANDARD 23)

# Common
add_library(aoc_common INTERFACE utils/dijkstra.c utils/dijkstra.h utils/cvec.c utils/cvec.h)

target_sources(aoc_common INTERFACE
        main.c
        utils/file_reader.c
        utils/cvec.c
        utils/linked_list.c)

target_include_directories(aoc_common INTERFACE
        utils/)


# Day executables (increase every day)
foreach(DAY RANGE 13)
    add_executable(D_${DAY} days/${DAY}.c)
    target_link_libraries(D_${DAY} aoc_common)
    target_compile_definitions(D_${DAY} PUBLIC INPUT_PATH="../inputs/${DAY}.txt")

    add_executable(T_${DAY} days/${DAY}.c)
    target_link_libraries(T_${DAY} aoc_common)
    target_compile_definitions(T_${DAY} PUBLIC INPUT_PATH="../tests/${DAY}.txt")
endforeach()
