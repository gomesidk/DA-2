cmake_minimum_required(VERSION 3.30)
project(untitled2)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled2 main.cpp
        menu.cpp
        menu.h
        data_loader.cpp
        data_loader.h
        dataset.h)
