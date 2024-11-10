cmake_minimum_required(VERSION 3.10)

project(DualListProcessor)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCES
    src/main.c
    src/list.c
    src/threads.c
)
add_executable(app ${SOURCES})
