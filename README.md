# Gesture-Based Presentation Clicker using ESP32 and MPU6050

## 📌 Overview

A wearable gesture-based presentation clicker designed to provide hands-free control of presentation slides.

The system uses an MPU6050 motion sensor to detect hand tilting gestures. An ESP32 processes the sensor data and sends keyboard commands wirelessly to a laptop using Bluetooth Low Energy (BLE).

## 🎯 Problem Statement

Traditional presentation clickers require physical buttons and interaction.

This project aims to develop a gesture-based presentation controller that allows presenters to navigate slides using simple hand movements without physically pressing buttons.

## ✨ Objectives

- Develop a hands-free presentation control system.
- Detect hand movements using the MPU6050 motion sensor.
- Process motion data using ESP32.
- Control presentation slides wirelessly.
- Create a compact wearable prototype.

## 🧰 Hardware

- ESP32 Development Board
- MPU6050 Motion Sensor
- 3.7V Li-ion Battery
- Breadboard
- Jumper Wires

## 💻 Software

- Arduino IDE
- ESP32 Board Package
- MPU6050 Library
- Wire Library
- BleKeyboard Library
- ThingSpeak

## ⚙️ System Architecture

```text
Hand Gesture
     ↓
MPU6050 Motion Sensor
     ↓
I²C Communication
     ↓
ESP32
     ↓
Gesture Detection
     ↓
Bluetooth
     ↓
Laptop
     ↓
Presentation Slide Control
🖐️ Gesture Controls
| Gesture       | Action         |
| ------------- | -------------- |
| Right Tilt    | Next Slide     |
| Left Tilt     | Previous Slide |
| Upward Tilt   | First Slide    |
| Downward Tilt | Last Slide     |
🔌 Communication

The MPU6050 communicates with the ESP32 using the I²C interface.

ESP32 I²C connections:

SDA → GPIO 21
SCL → GPIO 22

The ESP32 then communicates with the laptop wirelessly using Bluetooth.

☁️ IoT / Cloud Extension

An additional version of the project was developed using Wi-Fi and ThingSpeak.

The system can upload:

Accelerometer X-axis data
Accelerometer Y-axis data
Gesture code

to ThingSpeak for remote monitoring and visualization.

📊 Results

The prototype successfully detected hand tilt gestures and translated them into keyboard commands for presentation navigation.

📷 Project Photos

Project images will be added here.

🎥 Demonstration

A demonstration video will be added here.

🚀 Future Improvements
Add more gesture types.
Improve gesture recognition accuracy.
Add gyroscope-based orientation detection.
Develop a custom mobile/desktop interface.
Improve wearable enclosure design.
Reduce power consumption.
Explore machine-learning-based gesture recognition.
👩‍💻 Team

Developed as an academic IoT project by the project team at KLE Technological University.

📚 Learning Outcomes

Through this project, we explored:

ESP32 programming
MPU6050 interfacing
I²C communication
BLE communication
Gesture detection
IoT/cloud monitoring
Embedded system development
Hardware prototyping
