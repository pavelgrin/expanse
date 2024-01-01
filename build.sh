#! /bin/sh

BUILD_TYPE="Release"

while getopts d flag
do
    case "${flag}" in
        d) BUILD_TYPE="Debug";
    esac
done

mkdir -p .build
cmake -D CMAKE_BUILD_TYPE=$BUILD_TYPE -B ./.build -S .
cmake --build ./.build
