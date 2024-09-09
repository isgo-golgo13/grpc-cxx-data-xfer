# GRPC C++ Data Xfer
C++20 gRPC Client and Server Data Transfer Service using Buf Build gRPC Generator


## Project Directory Structure

```shell
/grpc-cxx-data-xfer
├── CMakeLists.txt
├── Dockerfile.client
├── Dockerfile.server
├── README.md
├── client/
│   └── main.cpp
├── server/
│   └── main.cpp
├── svckit-proto/
│   └── proto/
│       ├── service.proto
├── cmake/
│   └── FindProtobuf.cmake
└── build/  # This will be created after building
```

## Generate Protobuf Files

```shell
protoc --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` svckit-proto/proto/service.proto
```
This will generate the following files.

- `service.pb.h`, `service.pb.cc`: Protobuf message definitions`.
- `service.grpc.pb.h`, `service.grpc.pb.cc`: gRPC service stubs.


## Compile with CMake

The CMakeLists.txt project file is as follows.

```cmake
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
```

```shell
mkdir build
cmake -S . -B ./build
cd build
make
```


## Compile the Docker Images

```shell
docker build -f Dockerfile.server -t cpp-grpc-server .
docker build -f Dockerfile.client -t cpp-grpc-client .
```

## Run the Docker Containers

Run the server.
```shell
docker run -p 50051:50051 cpp-grpc-server
```

Run the client.
```shell
docker run cpp-grpc-client
```
