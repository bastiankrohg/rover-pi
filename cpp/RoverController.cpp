#include "RoverController.h"
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <cmath>

// GPIO pins configuration
#define MOTOR_LEFT_FORWARD 16
#define MOTOR_LEFT_BACKWARD 19
#define MOTOR_RIGHT_FORWARD 12
#define MOTOR_RIGHT_BACKWARD 13
#define HEADLIGHT_PIN 4
#define ULTRASONIC_TRIGGER 23
#define ULTRASONIC_ECHO 23
#define SERVO_PIN 5
#define WHEEL_LED_BASE_PIN 6

RoverController::RoverController() {}

RoverController::~RoverController() {
    cleanup();
}

void RoverController::init() {
    std::cout << "Initializing hardware..." << std::endl;

    // Initialize WiringPi
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "Failed to initialize WiringPi!" << std::endl;
        exit(1);
    }

    // Configure motor pins
    pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
    pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
    pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
    pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);

    // Configure headlights
    pinMode(HEADLIGHT_PIN, OUTPUT);

    // Configure ultrasonic sensor pins
    pinMode(ULTRASONIC_TRIGGER, OUTPUT);
    pinMode(ULTRASONIC_ECHO, INPUT);

    // Configure servo pin
    softPwmCreate(SERVO_PIN, 0, 200);

    // Configure wheel LED pins
    for (int i = 0; i < 6; i++) {
        softPwmCreate(WHEEL_LED_BASE_PIN + i, 0, 100);
    }

    std::cout << "Hardware initialized successfully." << std::endl;
}

void RoverController::cleanup() {
    std::cout << "Cleaning up hardware..." << std::endl;

    // Stop motors and turn off all LEDs
    stopMovement();
    digitalWrite(HEADLIGHT_PIN, LOW);
    for (int i = 0; i < 6; i++) {
        softPwmWrite(WHEEL_LED_BASE_PIN + i, 0);
    }

    std::cout << "Hardware cleanup complete." << std::endl;
}

// Locomotion
void RoverController::driveForward(float speed) {
    std::cout << "Driving forward at speed " << speed << std::endl;
    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void RoverController::reverse(float speed) {
    std::cout << "Reversing at speed " << speed << std::endl;
    digitalWrite(MOTOR_LEFT_FORWARD, LOW);
    digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
    digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
}

void RoverController::turnLeft(float angle) {
    std::cout << "Turning left at angle " << angle << std::endl;
    digitalWrite(MOTOR_LEFT_FORWARD, LOW);
    digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

void RoverController::turnRight(float angle) {
    std::cout << "Turning right at angle " << angle << std::endl;
    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
    digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
}

void RoverController::stopMovement() {
    std::cout << "Stopping all movement." << std::endl;
    digitalWrite(MOTOR_LEFT_FORWARD, LOW);
    digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
    digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
}

// Sensors
float RoverController::getUltrasoundMeasurement() {
    std::cout << "Measuring distance using ultrasonic sensor..." << std::endl;

    // Send trigger pulse
    digitalWrite(ULTRASONIC_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER, LOW);

    // Wait for echo pulse
    while (digitalRead(ULTRASONIC_ECHO) == LOW);
    long startTime = micros();

    while (digitalRead(ULTRASONIC_ECHO) == HIGH);
    long endTime = micros();

    // Calculate distance
    float distance = (endTime - startTime) * 0.0343 / 2.0;
    std::cout << "Distance: " << distance << " cm" << std::endl;

    return distance;
}

// LED Control
void RoverController::setHeadlights(bool on) {
    std::cout << (on ? "Turning headlights ON." : "Turning headlights OFF.") << std::endl;
    digitalWrite(HEADLIGHT_PIN, on ? HIGH : LOW);
}

void RoverController::setWheelLED(int wheelNumber, bool on) {
    if (wheelNumber < 0 || wheelNumber >= 6) {
        std::cerr << "Invalid wheel number: " << wheelNumber << std::endl;
        return;
    }
    std::cout << "Setting LED " << wheelNumber << " to " << (on ? "ON" : "OFF") << std::endl;
    softPwmWrite(WHEEL_LED_BASE_PIN + wheelNumber, on ? 100 : 0);
}

// Servo Control
void RoverController::rotatePeriscope(float angle) {
    std::cout << "Rotating periscope to " << angle << " degrees" << std::endl;
    int pulseWidth = static_cast<int>((angle / 180.0) * 200);
    softPwmWrite(SERVO_PIN, pulseWidth);
}