#include <grpcpp/grpcpp.h>
#include "RoverServiceImpl.h"

int main() {
    const std::string server_address("0.0.0.0:50051");  // Listen on all interfaces
    RoverServiceImpl service;  // Create the service implementation

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server is listening on " << server_address << std::endl;

    server->Wait();
    return 0;
}