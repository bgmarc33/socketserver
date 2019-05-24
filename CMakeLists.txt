cmake_minimum_required(VERSION 3.12)
project(unixsocket)

set(CMAKE_CXX_STANDARD 14)

link_libraries(pthread)
add_executable(unixsocket src/main.cpp src/SocketListener.cpp src/SocketListener.h src/ClientHandler.cpp src/ClientHandler.h)