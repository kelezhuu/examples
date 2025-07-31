cmake_minimum_required(VERSION 3.15)
project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(DEFAULT_COLOR "${Esc}[m")
  set(BLUE_COLOR    "${Esc}[34m")
  set(GREEN_COLOR   "${Esc}[32m")
endif()

set(GRPC_CPP_PLUGIN_EXECUTABLE "/home/galiyu/env/grpc/bin/grpc_cpp_plugin")

message(STATUS "${BLUE_COLOR}protobuf version${DEFAULT_COLOR}: ${Protobuf_VERSION}")
message(STATUS "${BLUE_COLOR}gRPC version${DEFAULT_COLOR}: ${gRPC_VERSION}")

set(PROTO_GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${PROTO_GEN_DIR})

include_directories(${PROTO_GEN_DIR})

add_subdirectory(protos)

add_subdirectory(servers)

add_subdirectory(clients)
