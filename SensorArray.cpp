#include <Arduino.h>

#include <SensorArray.h>

SensorArray::SensorArray(int leftSensor, int middleSensor, int rightSensor, int leftMotor, int rightMotor) {
    leftSensorPin = leftSensor;
    middleSensorPin = middleSensor;
    rightSensorPin = rightSensor;
    leftMotorPin = leftMotor;
    rightMotorPin = rightMotor;
    stopTimer = 0;
}

void SensorArray::begin() {
    pinMode(leftSensorPin, INPUT);
    pinMode(middleSensorPin, INPUT);
    pinMode(rightSensorPin, INPUT);
    pinMode(leftMotorPin, OUTPUT);
    pinMode(rightMotorPin, OUTPUT);
}

void SensorArray::turnLeft() {
    digitalWrite(leftMotorPin, LOW);
    digitalWrite(rightMotorPin, HIGH);
}

void SensorArray::moveForward() {
    digitalWrite(leftMotorPin, HIGH);
    digitalWrite(rightMotorPin, HIGH);
}

void SensorArray::turnRight() {
    digitalWrite(leftMotorPin, HIGH);
    digitalWrite(rightMotorPin, LOW);
}

void SensorArray::halt() {
    digitalWrite(leftMotorPin, LOW);
    digitalWrite(rightMotorPin, LOW);
}

void SensorArray::update() {
    int leftValue = digitalRead(leftSensorPin);
    int midValue = digitalRead(middleSensorPin);
    int rightValue = digitalRead(rightSensorPin);

    if (leftValue == 1 && midValue == 0 && rightValue == 0) {
        turnLeft();
        stopTimer = millis();
    } else if (leftValue == 0 && midValue == 0 && rightValue == 1) {
        turnRight();
        stopTimer = millis();
    } else if (midValue == 1 && leftValue == 0 && rightValue == 0) {
        moveForward();
        stopTimer = millis();
    } else if (midValue == 1 && leftValue == 0 && rightValue == 1) {
        moveForward();
        stopTimer = millis();
    } else if (midValue == 1 && leftValue == 1 && rightValue == 1) {
        if (millis() - stopTimer >= stopThreshold) {
            halt();
        }
    } else {
        stopTimer = millis();
    }
}
