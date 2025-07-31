add_executable(client_main
    main.cpp
)

target_link_libraries(client_main
    PUBLIC
    gRPC::grpc++
    protobuf::libprotobuf
    service_grpc_proto
)

add_dependencies(client_main service_grpc_proto)
