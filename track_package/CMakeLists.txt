cmake_minimum_required(VERSION 3.16)
project(track_package LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(track_package src/frameworks/cli/main.cpp)
target_include_directories(track_package PRIVATE src)
