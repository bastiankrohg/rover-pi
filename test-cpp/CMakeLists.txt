cmake_minimum_required(VERSION 3.10)

project(mars_rover)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find gRPC and Protobuf Packages
find_package(gRPC REQUIRED)
find_package(Protobuf REQUIRED)

# Include Directories
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${gRPC_INCLUDE_DIRS})
include_directories(../rover-protos)  # Include the rover-protos directory

# Add the generated Protobuf and gRPC files from rover-protos
set(PROTO_SRCS
    ../rover-protos/mars_rover.pb.cc
    ../rover-protos/mars_rover.grpc.pb.cc
)
set(PROTO_HDRS
    ../rover-protos/mars_rover.pb.h
    ../rover-protos/mars_rover.grpc.pb.h
)

# Add source files
set(SERVER_SRCS
    main.cpp
    TestRoverController.cpp
    TestRoverServiceImpl.cpp
    ${PROTO_SRCS}
)

# Add the server executable
add_executable(server ${SERVER_SRCS})

# Link the server with gRPC and Protobuf libraries
target_link_libraries(server
    gRPC::grpc++
    protobuf::libprotobuf
)