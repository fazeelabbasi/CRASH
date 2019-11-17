# CMakeList.txt : CMake project for Server, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Server "main.cpp" "Server.cpp" "Server.h" "Client.cpp" "Client.h")

# TODO: Add tests and install targets if needed.
