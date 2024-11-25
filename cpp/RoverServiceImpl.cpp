#include "RoverServiceImpl.h"

RoverServiceImpl::RoverServiceImpl() {
    roverController.init();
}

RoverServiceImpl::~RoverServiceImpl() {
    roverController.cleanup();
}

grpc::Status RoverServiceImpl::DriveForward(grpc::ServerContext* context, const marsrover::DriveRequest* request, marsrover::CommandResponse* response) {
    roverController.driveForward(request->speed());
    response->set_success(true);
    response->set_message("Driving forward");
    return grpc::Status::OK;
}

grpc::Status RoverServiceImpl::Reverse(grpc::ServerContext* context, const marsrover::DriveRequest* request, marsrover::CommandResponse* response) {
    roverController.reverse(request->speed());
    response->set_success(true);
    response->set_message("Reversing");
    return grpc::Status::OK;
}