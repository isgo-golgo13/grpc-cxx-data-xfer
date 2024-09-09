#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "service.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using namespace svckit;

class DataTransferServiceImpl final : public DataTransfer::Service {
public:
    Status Send(ServerContext* context, const SendRequest* request, SendResponse* response) override {
        response->set_bytes_transferred(request->data().size());
        return Status::OK;
    }

    Status SendAll(ServerContext* context, const SendAllRequest* request, SendResponse* response) override {
        int64_t total_bytes = 0;
        for (const auto& data : request->data()) {
            total_bytes += data.size();
        }
        response->set_bytes_transferred(total_bytes);
        return Status::OK;
    }

    Status Receive(ServerContext* context, const ReceiveRequest* request, ReceiveResponse* response) override {
        response->set_data(std::string(request->size(), 'x'));  // Simulate receiving data
        return Status::OK;
    }

    Status ReceiveAll(ServerContext* context, const ReceiveAllRequest* request, ReceiveResponse* response) override {
        std::string data;
        for (const auto& size : request->sizes()) {
            data += std::string(size, 'x');
        }
        response->set_data(data);
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    DataTransferServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main() {
    RunServer();
    return 0;
}
