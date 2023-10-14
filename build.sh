#! /bin/sh

BUILD_TYPE="Release"

while getopts d flag
do
    case "${flag}" in
        d) BUILD_TYPE="Debug";
    esac
done

mkdir -p .build
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -B ./.build -S .
cmake --build ./.build
