import grpc
from concurrent import futures
import signal
import sys
import rover
import rover_protos.mars_rover_pb2
from rover_protos import mars_rover_pb2_grpc


class Pi(mars_rover_pb2_grpc.RoverServiceServicer):
    def __init__(self):
        rover.init(0)  # Initialize hardware (GPIO, PCA9685, etc.)
        print("Rover initialized")

    # === Locomotion ===
    def DriveForward(self, request, context):
        speed = request.speed
        rover.forward(speed)
        return mars_rover_pb2.CommandResponse(
            success=True, message=f"Driving forward at speed {speed}"
        )

    def Reverse(self, request, context):
        speed = request.speed
        rover.reverse(speed)
        return mars_rover_pb2.CommandResponse(
            success=True, message=f"Reversing at speed {speed}"
        )

    def TurnLeft(self, request, context):
        angle = request.angle
        rover.spinLeft(angle)
        return mars_rover_pb2.CommandResponse(
            success=True, message=f"Turning left at angle {angle}"
        )

    def TurnRight(self, request, context):
        angle = request.angle
        rover.spinRight(angle)
        return mars_rover_pb2.CommandResponse(
            success=True, message=f"Turning right at angle {angle}"
        )

    def RotateOnSpot(self, request, context):
        angle = request.angle
        rover.spinLeft(angle) if angle > 0 else rover.spinRight(-angle)
        return mars_rover_pb2.CommandResponse(
            success=True, message=f"Rotating on spot by {angle} degrees"
        )

    def StopMovement(self, request, context):
        rover.stop()
        return mars_rover_pb2.CommandResponse(
            success=True, message="Movement stopped"
        )

    # === Sensors ===
    def GetUltrasoundMeasurement(self, request, context):
        distance = rover.getDistance()
        return mars_rover_pb2.UltrasoundResponse(
            distance=distance
        )

    def GetLightIntensity(self, request, context):
        intensity = rover.getLight()
        return mars_rover_pb2.LightResponse(
            intensity=intensity
        )

    # === LED Control ===
    def ControlHeadlights(self, request, context):
        on = request.on
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
        rover.setServo(0, angle)
        return mars_rover_pb2.CommandResponse(
            success=True,
            message=f"Periscope rotated to {angle} degrees"
        )

    def CalibrateServo(self, request, context):
        servo_number = request.servo_number
        angle = request.angle
        rover.setServo(servo_number, angle)
        return mars_rover_pb2.CommandResponse(
            success=True,
            message=f"Servo {servo_number} calibrated to {angle} degrees"
        )

    # === Cleanup ===
    def __del__(self):
        rover.cleanup()


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    mars_rover_pb2_grpc.add_RoverServiceServicer_to_server(Pi(), server)
    server.add_insecure_port('[::]:50051')
    print("Pi gRPC server started")

    # Graceful shutdown on Ctrl+C
    def signal_handler(sig, frame):
        rover.cleanup()
        server.stop(0)
        print("Server stopped")
        sys.exit(0)

    signal.signal(signal.SIGINT, signal_handler)
    server.start()
    server.wait_for_termination()


if __name__ == "__main__":
    serve()
