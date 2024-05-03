cmake_minimum_required(VERSION 3.27)
project(2048bot)

set(CMAKE_CXX_STANDARD 17)

add_executable(2048bot main.cpp
        utils.cpp
        utils.h
)
