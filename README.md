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
