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