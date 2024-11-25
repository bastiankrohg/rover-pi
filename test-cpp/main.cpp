#include <grpcpp/grpcpp.h>
#include "TestRoverServiceImpl.h"

int main() {
    // Define the server address
    const std::string server_address("0.0.0.0:50051");  // Listen on all interfaces

    // Create the service implementation
    TestRoverServiceImpl service;

    // Build the gRPC server
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    // Start the server
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server is listening on " << server_address << std::endl;

    // Wait for the server to shut down
    server->Wait();

    return 0;
}