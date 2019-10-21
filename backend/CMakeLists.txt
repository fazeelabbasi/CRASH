cmake_minimum_required(VERSION 3.15)
project(avatar)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -s -O3")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -static")
link_libraries(ws2_32 wsock32)

include_directories(
        "${CMAKE_SOURCE_DIR}/libs/cpp-webserver"
        "${CMAKE_SOURCE_DIR}/libs/cpp-webserver/socket/src"
        "${CMAKE_SOURCE_DIR}/libs/cpp-webserver/base64"
)

set(SOURCE_FILES
        core/GameHost.cpp
        core/GameHost.h
        core/Round.cpp
        core/Round.h
        core/User.cpp
        core/User.h
        main.cpp
        main.h
)

set(LIBRARY_FILES
        libs/cpp-webserver/base64/base64.cpp
        libs/cpp-webserver/base64/base64.h
        libs/cpp-webserver/socket/src/Socket.cpp
        libs/cpp-webserver/socket/src/Socket.h
        libs/cpp-webserver/webserver.cpp
        libs/cpp-webserver/webserver.h
        libs/cpp-webserver/stdHelpers.cpp
        libs/cpp-webserver/stdHelpers.h
        libs/cpp-webserver/UrlHelper.cpp
        libs/cpp-webserver/UrlHelper.h
)

add_executable(avatar
    ${LIBRARY_FILES}
    ${SOURCE_FILES}
)
