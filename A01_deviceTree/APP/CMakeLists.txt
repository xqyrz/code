cmake_minimum_required(VERSION 3.27)
project(ledAPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(ledAPP main.cpp
        cahrdevapp.cpp
        chardevapp.h
        ledapp.cpp
        ledapp.h)
