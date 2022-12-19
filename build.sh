#! /bin/sh

BUILD_TYPE="Release"

while getopts d flag
do
    case "${flag}" in
        d) BUILD_TYPE="Debug";
    esac
done

mkdir -p .build
cd .build
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
cmake --build .
cd ..
