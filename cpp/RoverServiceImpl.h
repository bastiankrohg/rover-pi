#ifndef ROVER_SERVICE_IMPL_H
#define ROVER_SERVICE_IMPL_H

#include "mars_rover.grpc.pb.h"
#include "RoverController.h"

class RoverServiceImpl final : public marsrover::RoverService::Service {
public:
    RoverServiceImpl();
    ~RoverServiceImpl();

    grpc::Status DriveForward(grpc::ServerContext* context, const marsrover::DriveRequest* request, marsrover::CommandResponse* response) override;
    grpc::Status Reverse(grpc::ServerContext* context, const marsrover::DriveRequest* request, marsrover::CommandResponse* response) override;
    // Add other gRPC methods here...

private:
    RoverController roverController;
};

#endif // ROVER_SERVICE_IMPL_H