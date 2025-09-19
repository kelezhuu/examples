cmake_minimum_required(VERSION 3.20)

project(socket-example)

add_executable(socket-server server.cpp)

add_executable(socket-client client.cpp)