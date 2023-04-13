cmake_minimum_required(VERSION 3.23)
project(M4OEP_wchrisma)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(M4OEP_wchrisma
        Button.cpp
        Button.h
        graphics.cpp
        graphics.h
        Quad.cpp
        Quad.h)
