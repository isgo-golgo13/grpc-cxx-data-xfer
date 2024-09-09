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
