cmake_minimum_required(VERSION 3.10)

project(MyProject VERSION 1.0)

enable_language(C)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(SOURCES
    src/main.c
)

set(TEST_SOURCES
    test/test.c
)

add_executable(my_executable ${SOURCES})
add_library(my_library STATIC ${SOURCES})
add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests PRIVATE my_library)
