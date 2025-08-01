# grpc-example

## Depends

但是下的时候似乎直接下载 gRPC 就可以了, ../grpc/lib/cmake/ 下存放着所有的依赖项.

```bash
gRPC、Protobuf、absl、utf8_range.
```

## CMake

按照实际情况修改路径, 有点 bug 需要指定 grpc_cpp_plugin 的位置.

```bash
cmake .. \
-DgRPC_DIR=/home/galiyu/env/grpc/lib/cmake/grpc \
-DProtobuf_DIR=/home/galiyu/env/grpc/lib/cmake/protobuf \
-Dutf8_range_DIR=/home/galiyu/env/grpc/lib/cmake/utf8_range \
-Dabsl_DIR=/home/galiyu/env/grpc/lib/cmake/absl
```

## protos

CMake 框架写好了, 后续要增加 .proto 文件直接在 protos/ 中添加即可, 代码生成位置在 build/generated/ 下.

## servers

服务器的启动是公式化的, 一般就改一下服务类的初始化参数即可.

主要还是服务类中的函数的实现, 服务类中的函数一般是被客户端给调用, stream 的读和写都是会反映到客户端上, 而在函数体内的打印等操作则是会打印在服务端的终端中.

服务器的函数返回值是一个 Status 对象.

## clients

客户端的类一般不会从什么地方继承过来, 基础的话一般会带一个 unique_ptr<xxx::Stub> stub_ 的参数, 这个实例化对象负责与服务器的传输流, 调用函数也是从这个实例化对象中调用.

一般双向流的读写, 就需要在客户端中多开线程, 主线程负责读取, 子线程负责写入.

