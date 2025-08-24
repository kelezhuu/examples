## 环境依赖的安装

新版一点的 leveldb 现在添加了 C++17 的依赖，编译的时候需要启用 C++17 的标准。

然后如果 CMAKE 版本太高也可能有点问题。

```
# leveldb 

cmake .. -G Ninja \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX=xxx

ninja -j6

ninja install
```

## 编译

```
-Dleveldb_DIR=/Users/galiyu/env/leveldb/lib/cmake/leveldb
```

MACOS：
C / C++ 编译器使用 clang。

## 调试

如果需要调试 leveldb 的源码，cmakelists 需要改成这样。

对应的静态链接 leveldb 这个库，这样编译时间会长点。

```
cmake_minimum_required(VERSION 3.20)
project(learn_leveldb)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)

# 添加 LevelDB 源码目录
add_subdirectory(/Users/galiyu/project/leveldb leveldb_build)

add_executable(leveldb-example main.cpp)

target_link_libraries(leveldb-example
        PRIVATE
        leveldb
        Threads::Threads
)
```