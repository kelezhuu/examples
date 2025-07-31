# grpc-example

## Depends

但是下的时候似乎直接下载 gRPC 就可以了, ../grpc/lib/cmake/ 下存放着所有的依赖项.

```bash
gRPC、Protobuf、absl、utf8_range.
```

## CMake

按照实际情况修改路径, 有点 bug 需要制定 grpc_cpp_plugin 的位置.

```bash
cmake .. -DgRPC_DIR=/home/galiyu/env/grpc/lib/cmake/grpc -DProtobuf_DIR=/home/galiyu/env/grpc/lib/cmake/protobuf -Dutf8_range_DIR=/home/galiyu/env/grpc/lib/cmake/utf8_range -Dabsl_DIR=/home/galiyu/env/grpc/lib/cmake/absl
```

## protos

CMake 框架写好了, 后续要增加 .proto 文件直接在 protos/ 中添加即可, 代码生成位置在 build/generated/ 下.

## clients



## servers