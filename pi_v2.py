import grpc
from concurrent import futures
import signal
import sys
import rover
from rover_protos import mars_rover_pb2
from rover_protos import mars_rover_pb2_grpc


class Pi(mars_rover_pb2_grpc.RoverServiceServicer):
    def __init__(self):
        print("[DEBUG] Initializing the Rover hardware...")
        rover.init(0)  # Initialize hardware (GPIO, PCA9685, etc.)
        print("[DEBUG] Rover initialized successfully")

    # === Locomotion ===
    def DriveForward(self, request, context):
        speed = request.speed
        print(f"[DEBUG] DriveForward called with speed={speed}")
        rover.forward(speed)
        return mars_rover_pb2.CommandResponse(
            success=True, message=f"Driving forward at speed {speed}"
        )

    def Reverse(self, request, context):
        speed = request.speed
        print(f"[DEBUG] Reverse called with speed={speed}")
        rover.reverse(speed)
        return mars_rover_pb2.CommandResponse(
            success=True, message=f"Reversing at speed {speed}"
        )

    def TurnLeft(self, request, context):
        angle = request.angle
        print(f"[DEBUG] TurnLeft called with angle={angle}")
        rover.spinLeft(angle)
        return mars_rover_pb2.CommandResponse(
            success=True, message=f"Turning left at angle {angle}"
        )

    def TurnRight(self, request, context):
        angle = request.angle
        print(f"[DEBUG] TurnRight called with angle={angle}")
        rover.spinRight(angle)
        return mars_rover_pb2.CommandResponse(
            success=True, message=f"Turning right at angle {angle}"
        )

    def RotateOnSpot(self, request, context):
        angle = request.angle
        print(f"[DEBUG] RotateOnSpot called with angle={angle}")
        rover.spinLeft(angle) if angle > 0 else rover.spinRight(-angle)
        return mars_rover_pb2.CommandResponse(
            success=True, message=f"Rotating on spot by {angle} degrees"
        )

    def StopMovement(self, request, context):
        print("[DEBUG] StopMovement called")
        rover.stop()
        return mars_rover_pb2.CommandResponse(
            success=True, message="Movement stopped"
        )

    # === Sensors ===
    def GetUltrasoundMeasurement(self, request, context):
        print("[DEBUG] GetUltrasoundMeasurement called")
        distance = rover.getDistance()
        return mars_rover_pb2.UltrasoundResponse(
            distance=distance
        )

    def GetLightIntensity(self, request, context):
        print("[DEBUG] GetLightIntensity called")
        intensity = rover.getLight()
        return mars_rover_pb2.LightResponse(
            intensity=intensity
        )

    # === LED Control ===
    def ControlHeadlights(self, request, context):
        on = request.on
        print(f"[DEBUG] ControlHeadlights called with on={on}")
        color = rover.fromRGB(255, 255, 255) if on else rover.fromRGB(0, 0, 0)
        rover.setColor(color)
        rover.show()
        return mars_rover_pb2.CommandResponse(
            success=True,
            message="Headlights turned on" if on else "Headlights turned off"
        )

    def ControlWheelLEDs(self, request, context):
        wheel_number = request.wheel_number
        on = request.on
        print(f"[DEBUG] ControlWheelLEDs called for wheel {wheel_number} with on={on}")
        color = rover.fromRGB(0, 255, 0) if on else rover.fromRGB(0, 0, 0)
        rover.setPixel(wheel_number, color)
        rover.show()
        return mars_rover_pb2.CommandResponse(
            success=True,
            message=f"Wheel LED {wheel_number} {'on' if on else 'off'}"
        )

    # === Servo Control ===
    def RotatePeriscope(self, request, context):
        angle = request.angle
        print(f"[DEBUG] RotatePeriscope called with angle={angle}")
        rover.setServo(0, angle)
        return mars_rover_pb2.CommandResponse(
            success=True,
            message=f"Periscope rotated to {angle} degrees"
        )

    def CalibrateServo(self, request, context):
        servo_number = request.servo_number
        angle = request.angle
        print(f"[DEBUG] CalibrateServo called with servo_number={servo_number}, angle={angle}")
        rover.setServo(servo_number, angle)
        return mars_rover_pb2.CommandResponse(
            success=True,
            message=f"Servo {servo_number} calibrated to {angle} degrees"
        )

    # === Cleanup ===
    def __del__(self):
        print("[DEBUG] Cleaning up Rover resources")
        rover.cleanup()


def serve():
    print("[DEBUG] Starting Pi gRPC server...")
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    mars_rover_pb2_grpc.add_RoverServiceServicer_to_server(Pi(), server)
    server.add_insecure_port('[::]:50051')
    print("[DEBUG] Pi gRPC server started and listening on port 50051")

    # Graceful shutdown on Ctrl+C
    def signal_handler(sig, frame):
        print("[DEBUG] SIGINT received, stopping server...")
        rover.cleanup()
        server.stop(0)
        print("[DEBUG] Server stopped successfully")
        sys.exit(0)

    signal.signal(signal.SIGINT, signal_handler)
    server.start()
    server.wait_for_termination()


if __name__ == "__main__":
    print("[DEBUG] Pi gRPC application starting...")
    serve()