cmake_minimum_required(VERSION 3.0)
project(StrUtil C)

# List the header file(s) and source file(s)
set(HEADERS
    strutil.h
)

set(SOURCES
    main.c  # If there's a sample application, include main.c here
)

# Create the compilation target
add_executable(strutil_example ${SOURCES})

# Include header files in the target
target_include_directories(strutil PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
