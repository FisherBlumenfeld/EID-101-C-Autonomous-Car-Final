// Define pins for ultrasonic sensor
const int echoPin = 13; // Echo pin
const int trigPin = A3; // Trig pin

// Define motor control pins
const int in1 = 5; // Motor 1 forward
const int in2 = 6; // Motor 1 backward
const int in3 = 7; // Motor 2 forward
const int in4 = 8; // Motor 2 backward

const int stopThreshold = 21; // Distance threshold in cm
// The sensor seems to be uncalibrated, but 21cm in the code equates to 30cm in real life
float duration, distance;

void setup() {
  // Setup ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Setup motor pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo signal
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  if (duration == 0) {
    distance = -1; // Invalid reading
  } else {
    distance = (duration * 0.0343) / 2;
  }

  // Print the distance for debugging
  Serial.print("Distance: ");
  if (distance == -1) {
    Serial.println("No object detected");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Control motors based on distance
  if (distance > 0 && distance <= stopThreshold) {
    stopMotors(); // Stop immediately if within threshold
  } else if (distance > stopThreshold) {
    moveForward(); // Move forward if safe distance
  }
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// Function to move forward
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
