#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

// Motor and Servo objects
AF_DCMotor M1(3);
Servo servo1;
char controlSignal;

// Ultrasonic
#define TRIG_PIN A0 
#define ECHO_PIN A1
#define MAX_DISTANCE 100 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // Initialize the ultrasonic sensor

// Variables for non-blocking servo movement
int servo_position = 0;
int step = 1;  // Controls the direction and speed of servo rotation
unsigned long previousMillis = 0; 
const long interval = 15;  // Time interval for each step in milliseconds
bool servoMoving = false;
bool motorRunning = false; 

// Distance threshold (12 cm)
const int distanceThreshold = 12;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1);

  // Attach the servo to pin 9 (change if needed)
  servo1.attach(10);

  pinMode(2, OUTPUT);
}

void loop() {
  
// Measure the distance using the ultrasonic sensor
  int distance = sonar.ping_cm();
  if (distance > 0 && distance <= distanceThreshold) {

       // Check for serial input for DC motor control and servo control
      if (Serial.available()) {
        controlSignal = Serial.read();
        switch (controlSignal) {
          case '1':
            M1.setSpeed(150);
            M1.run(BACKWARD);
            motorRunning = true; 
            break;
          case '2':
            M1.setSpeed(200);
            M1.run(BACKWARD);
            motorRunning = true;
            break;
          case '3':
            M1.setSpeed(255);
            M1.run(BACKWARD);
            motorRunning = true;
            break;
          case '4':
            if (motorRunning) {   // Only allow servo rotation if the motor is running
              servoMoving = true;  // Start servo rotation
            }
            break;
          case '5':
            servoMoving = false;  // Stop servo rotation
            break;
          default:
            M1.setSpeed(0);
            M1.run(RELEASE);  // Stop the DC motor
            servoMoving = false;  // Stop servo movement
            motorRunning = false;
            break;
        }
      }
      
  }
  
  // Non-blocking servo rotation
  if (servoMoving) {
    rotateServo();
  }
}

// Function to rotate the servo motor continuously between 0 and 180 degrees non-blocking
void rotateServo() {
  unsigned long currentMillis = millis();  // Get the current time

  // Check if the interval time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time the servo was updated

    // Update servo position
    servo_position += step;
    
    // Reverse direction if limits are reached
    if (servo_position >= 180 || servo_position <= 0) {
      step = -step;  // Reverse direction
    }
    
    // Write the new position to the servo
    servo1.write(servo_position);
  }
}
