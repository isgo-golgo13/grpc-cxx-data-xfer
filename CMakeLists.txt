cmake_minimum_required(VERSION 3.20)
project(grpc_microservice_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set project paths
set(PROTO_DIR ${CMAKE_SOURCE_DIR}/svckit-proto/proto)
set(PROTO_SRC_DIR ${CMAKE_BINARY_DIR}/generated)
set(CLIENT_SRC_DIR ${CMAKE_SOURCE_DIR}/client)
set(SERVER_SRC_DIR ${CMAKE_SOURCE_DIR}/server)

# Find Protobuf and gRPC packages
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# Protobuf and gRPC generation
file(GLOB PROTO_FILES "${PROTO_DIR}/*.proto")

# Generate C++ sources from .proto files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_FILES})

# Set output directory for generated files
set(GENERATED_PROTO_DIR ${PROTO_SRC_DIR})
file(MAKE_DIRECTORY ${GENERATED_PROTO_DIR})

# Include directories for generated protobuf files
include_directories(${GENERATED_PROTO_DIR} ${PROTOBUF_INCLUDE_DIRS} ${GRPC_INCLUDE_DIRS})

# Client executable
add_executable(client ${CLIENT_SRC_DIR}/main.cpp ${PROTO_SRCS} ${GRPC_SRCS})
target_link_libraries(client gRPC::grpc++ protobuf::libprotobuf)

# Server executable
add_executable(server ${SERVER_SRC_DIR}/main.cpp ${PROTO_SRCS} ${GRPC_SRCS})
target_link_libraries(server gRPC::grpc++ protobuf::libprotobuf)
