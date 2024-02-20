cmake_minimum_required(VERSION 3.10)

project(example_project)

add_compile_options(-Wall -Wextra -std=c11)

add_executable(example main.c)

target_include_directories(example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
