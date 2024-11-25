#ifndef TEST_ROVER_CONTROLLER_H
#define TEST_ROVER_CONTROLLER_H

#include <iostream>

class TestRoverController {
public:
    TestRoverController();
    ~TestRoverController();

    void init();                     // Initialize components
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

#endif // TEST_ROVER_CONTROLLER_H