cmake_minimum_required(VERSION 3.15)
project(avatar)

set(CMAKE_CXX_STANDARD 14)

add_executable(avatar main.cpp main.h core/GameHost.cpp core/GameHost.h core/Round.cpp core/Round.h core/User.cpp core/User.h)
