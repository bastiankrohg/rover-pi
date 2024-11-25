#include "TestRoverServiceImpl.h"

TestRoverServiceImpl::TestRoverServiceImpl() {
    roverController.init();  // Initialize the rover controller
}

TestRoverServiceImpl::~TestRoverServiceImpl() {
    roverController.cleanup();  // Clean up resources
}

grpc::Status TestRoverServiceImpl::DriveForward(grpc::ServerContext* context, const marsrover::DriveRequest* request, marsrover::CommandResponse* response) {
    roverController.driveForward(request->speed());
    response->set_success(true);
    response->set_message("Driving forward");
    return grpc::Status::OK;
}

grpc::Status TestRoverServiceImpl::Reverse(grpc::ServerContext* context, const marsrover::DriveRequest* request, marsrover::CommandResponse* response) {
    roverController.reverse(request->speed());
    response->set_success(true);
    response->set_message("Reversing");
    return grpc::Status::OK;
}

grpc::Status TestRoverServiceImpl::StopMovement(grpc::ServerContext* context, const marsrover::StopRequest* request, marsrover::CommandResponse* response) {
    roverController.stopMovement();
    response->set_success(true);
    response->set_message("Movement stopped");
    return grpc::Status::OK;
}