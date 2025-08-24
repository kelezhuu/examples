cmake_minimum_required(VERSION 3.20)
project(learn_leveldb)

set(CMAKE_CXX_STANDARD 17)

# 添加依赖
# 依赖 系统的 Threads 库 和 leveldb
find_package(Threads REQUIRED)
find_package(leveldb REQUIRED CONFIG)

message(STATUS "leveldb: v${leveldb_VERSION}")

set(_LEVELDB_TARGET leveldb::leveldb)
get_target_property(LEVELDB_INCLUDE "${_LEVELDB_TARGET}" INTERFACE_INCLUDE_DIRECTORIES)

message(STATUS "leveldb include dirs: ${LEVELDB_INCLUDE}")
message(STATUS "leveldb linking libs: ${_LEVELDB_TARGET}")

# 添加头文件
include_directories(${LEVELDB_INCLUDE})

add_executable(leveldb-example main.cpp)

# 链接库
target_link_libraries(leveldb-example
        PUBLIC
        ${_LEVELDB_TARGET}
        Threads::Threads
)