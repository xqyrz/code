cmake_minimum_required(VERSION 3.27)
#set(CMAKE_INSTALL_PREFIX "/home/xqyr/study/new_study/flie/nfs/root/opt" CACHE PATH "Installation prefix")
project(keyAPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp
        cahrdevapp.cpp
        chardevapp.h
        keyapp.cpp
        keyapp.h)

install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_NAME})