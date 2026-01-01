cmake_minimum_required(VERSION 4.1)
project(ac_mod)

set(CMAKE_CXX_STANDARD 20)

add_executable(ac_mod main.cpp
        process_finder/ProcessFinder.cpp
        process_finder/ProcessFinder.h)
