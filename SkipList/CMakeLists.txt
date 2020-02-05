cmake_minimum_required(VERSION 3.15)
project(source)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(source
        atomic_markable_reference.hpp
        main.cpp
        node.hpp
        skiplist.hpp)
