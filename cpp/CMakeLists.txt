cmake_minimum_required(VERSION 3.10)
project(mars_rover)

# Find gRPC and Protobuf packages
find_package(gRPC REQUIRED)
find_package(Protobuf REQUIRED)

# Add the generated files from .proto
set(PROTO_SRCS mars_rover.pb.cc mars_rover.grpc.pb.cc)
set(PROTO_HDRS mars_rover.pb.h mars_rover.grpc.pb.h)

# Add your own source files
set(SERVER_SRCS main.cpp RoverController.cpp RoverServiceImpl.cpp ${PROTO_SRCS})

# Build the server
add_executable(server ${SERVER_SRCS})
target_link_libraries(server gRPC::grpc++ protobuf::libprotobuf)