#ifndef SENSORARRAY_H
#define SENSORARRAY_H

#ifndef SENSORARRAY_H
#define SENSORARRAY_H

#include <Arduino.h>

class SensorArray {
  private:
    int leftSensorPin;
    int middleSensorPin;
    int rightSensorPin;
    int leftMotorPin;
    int rightMotorPin;

    unsigned long stopTimer;
    const unsigned long stopThreshold = 500;

    void moveForward();
    void turnLeft();
    void turnRight();
    void halt();

  public:
    SensorArray(int leftSensor, int middleSensor, int rightSensor, int leftMotor, int rightMotor);
    void begin();
    void update();
};

#endif

#endif // SENSORARRAY_H
