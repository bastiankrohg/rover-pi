#ifndef TEST_ROVER_SERVICE_IMPL_H
#define TEST_ROVER_SERVICE_IMPL_H

#include "mars_rover.grpc.pb.h"
#include "TestRoverController.h"

class TestRoverServiceImpl final : public marsrover::RoverService::Service {
public:
    TestRoverServiceImpl();   // Constructor
    ~TestRoverServiceImpl();  // Destructor

    grpc::Status DriveForward(grpc::ServerContext* context, const marsrover::DriveRequest* request, marsrover::CommandResponse* response) override;
    grpc::Status Reverse(grpc::ServerContext* context, const marsrover::DriveRequest* request, marsrover::CommandResponse* response) override;
grpc::Status StopMovement(grpc::ServerContext* context, const marsrover::StopRequest* request, marsrover::CommandResponse* response) override;
private:
    TestRoverController roverController;
};

#endif // TEST_ROVER_SERVICE_IMPL_H