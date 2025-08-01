add_executable(server_main
    main.cpp
)

target_link_libraries(server_main
    PUBLIC
    gRPC::grpc++
    protobuf::libprotobuf
    service_grpc_proto
)

add_dependencies(server_main service_grpc_proto)