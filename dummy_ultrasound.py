import random
import grpc
from concurrent import futures
from rover_protos import mars_rover_pb2, mars_rover_pb2_grpc


class MockUltrasoundService(mars_rover_pb2_grpc.RoverServiceServicer):
    def GetUltrasoundMeasurement(self, request, context):
        random_distance = random.randint(5, 100)
        print(f"[DEBUG] Generated random ultrasound measurement: {random_distance}")
        return mars_rover_pb2.UltrasoundResponse(distance=random_distance)


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    mars_rover_pb2_grpc.add_RoverServiceServicer_to_server(MockUltrasoundService(), server)
    server.add_insecure_port("[::]:50052")  # Using a different port for the mock server
    print("[DEBUG] Mock Ultrasound Server is running on port 50052.")
    server.start()
    server.wait_for_termination()


if __name__ == "__main__":
    serve()