#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "service.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace svckit;

class DataTransferClient {
public:
    explicit DataTransferClient(std::shared_ptr<Channel> channel)
        : stub_(DataTransfer::NewStub(channel)) {}

    void Send(const std::string& data) {
        SendRequest request;
        request.set_data(data);
        SendResponse response;
        ClientContext context;

        Status status = stub_->Send(&context, request, &response);
        if (status.ok()) {
            std::cout << "Bytes transferred: " << response.bytes_transferred() << std::endl;
        } else {
            std::cout << "RPC failed" << std::endl;
        }
    }

private:
    std::unique_ptr<DataTransfer::Stub> stub_;
};

int main() {
    DataTransferClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    std::string data = "Hello, world!";
    client.Send(data);

    return 0;
}
