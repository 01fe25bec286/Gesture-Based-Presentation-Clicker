#include <Wire.h>
#include <MPU6050.h>
#include <BleKeyboard.h>

MPU6050 mpu;

BleKeyboard bleKeyboard("ESP32 Gesture Controller");

// ===== MPU6050 VARIABLES =====
int16_t ax, ay, az;

// ===== GESTURE SETTINGS =====
const int THRESHOLD = 1200;
const unsigned long GESTURE_DELAY = 1200;

unsigned long lastGestureTime = 0;

void setup() {

  Serial.begin(115200);
  delay(1000);

  // Initialize I2C
  // SDA = GPIO 21
  // SCL = GPIO 22
  Wire.begin(21, 22);

  // Initialize MPU6050
  mpu.initialize();
  mpu.setSleepEnabled(false);

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully");
  } 
  else {
    Serial.println("MPU6050 connection failed");
  }

  // Start Bluetooth Keyboard
  bleKeyboard.begin();

  Serial.println("Bluetooth Keyboard Started");
}

void loop() {

  // ===== READ MPU6050 DATA =====
  mpu.getAcceleration(&ax, &ay, &az);

  // ===== SERIAL MONITOR =====
  Serial.print("AX: ");
  Serial.print(ax);

  Serial.print(" | AY: ");
  Serial.print(ay);

  Serial.print(" | AZ: ");
  Serial.println(az);

  // ===== GESTURE DETECTION =====
  if (millis() - lastGestureTime > GESTURE_DELAY) {

    // RIGHT TILT
    // NEXT SLIDE
    if (ax > THRESHOLD) {

      Serial.println("NEXT SLIDE");

      if (bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_RIGHT_ARROW);
      }

      lastGestureTime = millis();
    }

    // LEFT TILT
    // PREVIOUS SLIDE
    else if (ax < -THRESHOLD) {

      Serial.println("PREVIOUS SLIDE");

      if (bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_LEFT_ARROW);
      }

      lastGestureTime = millis();
    }

    // UPWARD TILT
    // FIRST SLIDE
    else if (ay < -THRESHOLD) {

      Serial.println("FIRST SLIDE");

      if (bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_HOME);
      }

      lastGestureTime = millis();
    }

    // DOWNWARD TILT
    // LAST SLIDE
    else if (ay > THRESHOLD) {

      Serial.println("LAST SLIDE");

      if (bleKeyboard.isConnected()) {
        bleKeyboard.write(KEY_END);
      }

      lastGestureTime = millis();
    }
  }

  // Small delay for stable readings
  delay(80);
}
