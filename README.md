# fan_speed_controller_v1.0.3
 This project for bulid a smart fan using python with arduino

Smart Gesture-Controlled Fan System 🖐️💨
Control your fan with simple hand gestures! This project combines computer vision and Arduino to create an interactive, gesture-controlled fan system with built-in safety features.
Overview
This smart fan system lets you control a fan's speed and rotation mode using hand gestures captured by your computer's webcam. It includes safety features like proximity detection to prevent accidents.
Features

👆 Control fan speed with finger gestures (0-3 fingers)
✋ Toggle rotation mode with 4-5 fingers
🛑 Automatic safety cutoff using ultrasonic sensor
📹 Real-time visual feedback on screen
🔄 Smooth servo-controlled rotation

How to Use
Gesture Controls

0 fingers: Turn fan OFF
1 finger: Turn fan ON (Speed 1)
2 fingers: Speed 2
3 fingers: Speed 3
4 fingers: Enable rotation mode
5 fingers: Disable rotation mode

Requirements
Hardware

Arduino board (compatible with AFMotor library)
DC motor (for fan)
Servo motor (for rotation)
Ultrasonic sensor (HC-SR04)
Webcam
USB cable
Power supply for Arduino

Software Dependencies
Python:

OpenCV (cv2)
CVZone
PySerial

Arduino:

AFMotor library
Servo library
NewPing library

Installation

Arduino Setup

Install required Arduino libraries through Arduino IDE
Upload sketch_oct07a.ino to your Arduino board
Connect hardware components:

DC motor to Motor port 3
Servo to pin 10
Ultrasonic sensor: TRIG to A0, ECHO to A1




Python Setup
bashCopypip install opencv-python
pip install cvzone
pip install pyserial

Configuration

Update the COM port in program.py if needed:
pythonCopyser = serial.Serial('COM3', 9600)  # Change COM3 to your port




Safety Features

The system includes an ultrasonic sensor that monitors proximity
Fan only operates when objects are at a safe distance (>12cm)
Rotation mode only works when the fan is running