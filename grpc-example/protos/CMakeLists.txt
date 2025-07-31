set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB PROTO_FILES "${PROTO_DIR}/*.proto")

foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)
    message(STATUS "found *.proto: ${PROTO_FILE}")

    set(PROTO_SRC      "${PROTO_GEN_DIR}/${PROTO_NAME}.pb.cc")
    set(PROTO_HDR      "${PROTO_GEN_DIR}/${PROTO_NAME}.pb.h")
    set(PROTO_GRPC_SRC "${PROTO_GEN_DIR}/${PROTO_NAME}.grpc.pb.cc")
    set(PROTO_GRPC_HDR "${PROTO_GEN_DIR}/${PROTO_NAME}.grpc.pb.h")

    add_custom_command(
        OUTPUT ${PROTO_SRC} ${PROTO_HDR} ${PROTO_GRPC_SRC} ${PROTO_GRPC_HDR}
        COMMAND protobuf::protoc
            --proto_path=${CMAKE_CURRENT_BINARY_DIR}
            --cpp_out=${PROTO_GEN_DIR}
            --grpc_out=${PROTO_GEN_DIR}
            --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_EXECUTABLE}
            -I ${CMAKE_CURRENT_SOURCE_DIR}
            ${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
    )

    list(APPEND PROTO_SOURCES ${PROTO_SRC} ${PROTO_GRPC_SRC})
endforeach()

add_custom_target(PROTO_OK ALL DEPENDS ${PROTO_SRC} ${PROTO_GRPC_SRC})

if(NOT PROTO_SOURCES)
    message(FATAL_ERROR "PROTO_SOURCES not found")
endif()

message(STATUS "PROTO_SOURCES:")
foreach(PROTO_FILE ${PROTO_SOURCES})
    message(STATUS "${PROTO_FILE}")
endforeach()

add_library(service_grpc_proto STATIC ${PROTO_SOURCES})

target_link_libraries(service_grpc_proto
    PUBLIC
    gRPC::grpc++
    protobuf::libprotobuf
)

target_include_directories(service_grpc_proto
    PUBLIC
    ${PROTO_GEN_DIR}
)
