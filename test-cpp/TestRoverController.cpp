#include "TestRoverController.h"

TestRoverController::TestRoverController() {}

TestRoverController::~TestRoverController() {
    cleanup();
}

void TestRoverController::init() {
    std::cout << "[INIT] Simulating hardware initialization..." << std::endl;
}

void TestRoverController::cleanup() {
    std::cout << "[CLEANUP] Simulating hardware cleanup..." << std::endl;
}

// Locomotion
void TestRoverController::driveForward(float speed) {
    std::cout << "[LOCOMOTION] Driving forward at speed " << speed << std::endl;
}

void TestRoverController::reverse(float speed) {
    std::cout << "[LOCOMOTION] Reversing at speed " << speed << std::endl;
}

void TestRoverController::turnLeft(float angle) {
    std::cout << "[LOCOMOTION] Turning left by " << angle << " degrees" << std::endl;
}

void TestRoverController::turnRight(float angle) {
    std::cout << "[LOCOMOTION] Turning right by " << angle << " degrees" << std::endl;
}

void TestRoverController::stopMovement() {
    std::cout << "[LOCOMOTION] Stopping all movement." << std::endl;
}

// Sensors
float TestRoverController::getUltrasoundMeasurement() {
    std::cout << "[SENSOR] Simulating distance measurement..." << std::endl;
    float dummyDistance = 42.0f;  // Example value
    std::cout << "[SENSOR] Measured distance: " << dummyDistance << " cm" << std::endl;
    return dummyDistance;
}

// LED Control
void TestRoverController::setHeadlights(bool on) {
    std::cout << "[LED] Headlights " << (on ? "ON" : "OFF") << std::endl;
}

void TestRoverController::setWheelLED(int wheelNumber, bool on) {
    std::cout << "[LED] Wheel LED " << wheelNumber << " set to " << (on ? "ON" : "OFF") << std::endl;
}

// Servo Control
void TestRoverController::rotatePeriscope(float angle) {
    std::cout << "[SERVO] Rotating periscope to " << angle << " degrees" << std::endl;
}