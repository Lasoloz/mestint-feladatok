cmake_minimum_required(VERSION 2.6)
project(amoba)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -Wpedantic")

include_directories(include)

add_executable(
    amoba
    src/amoba.cpp
    src/game/field.cpp
    src/game/local.cpp
    src/game/netPlay.cpp
    src/tcp/TcpException.cpp
    src/tcp/TcpSocket.cpp
    src/tcp/TcpListener.cpp
)

target_link_libraries(amoba pthread)
