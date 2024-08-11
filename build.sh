#!/bin/bash

PROJECT_DIR=$(pwd)

BUILD_DIR="${PROJECT_DIR}/build"
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR" || exit

cmake ..

make

if [ $? -eq 0 ]; then
    read -p "Do you want to run the main executable? (y/n): " CHOICE
    case "$CHOICE" in
        [yY])
            ./my_executable
            ;;
        *)
            echo "Main executable not run."
            ;;
    esac
else
    echo "Build failed."
fi
