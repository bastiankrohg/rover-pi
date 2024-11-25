#ifndef ROVER_CONTROLLER_H
#define ROVER_CONTROLLER_H

class RoverController {
public:
    RoverController();
    ~RoverController();

    void init();                     // Initialize GPIO and hardware
    void cleanup();                  // Cleanup resources

    // Locomotion
    void driveForward(float speed);
    void reverse(float speed);
    void turnLeft(float angle);
    void turnRight(float angle);
    void stopMovement();

    // Sensors
    float getUltrasoundMeasurement();

    // LED Control
    void setHeadlights(bool on);
    void setWheelLED(int wheelNumber, bool on);

    // Servo Control
    void rotatePeriscope(float angle);
};

#endif // ROVER_CONTROLLER_H