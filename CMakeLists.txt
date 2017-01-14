cmake_minimum_required(VERSION 2.8)
set(CMAKE_SYSTEM_NAME Windows)
project(leclock C)

add_subdirectory(dix)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(leclock ${SOURCE_FILES})