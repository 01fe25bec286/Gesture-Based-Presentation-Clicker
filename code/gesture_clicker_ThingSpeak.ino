#include <WiFi.h>
#include <Wire.h>
#include <MPU6050.h>
#include "ThingSpeak.h"

MPU6050 mpu;

WiFiClient client;

// ==================================================
// WIFI DETAILS
// ==================================================
// IMPORTANT:
// Replace these values ONLY in your local Arduino code.
// Do NOT upload your real Wi-Fi credentials to GitHub.

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ==================================================
// THINGSPEAK DETAILS
// ==================================================

unsigned long channelID = 3218768;

// IMPORTANT:
// Keep your real Write API Key private.
// Replace this only in your local copy.

const char* writeAPIKey = "YOUR_THINGSPEAK_WRITE_API_KEY";

// ==================================================
// MPU6050 VARIABLES
// ==================================================

int16_t ax, ay, az;

// Gesture sensitivity
const int threshold = 12000;

// Time between cloud updates
const unsigned long UPDATE_INTERVAL = 15000;

unsigned long lastUpdate = 0;

// Gesture code
// 0 = Stable
// 1 = Next Slide
// 2 = Previous Slide

int gestureCode = 0;

void setup() {

  // ==================================================
  // SERIAL COMMUNICATION
  // ==================================================

  Serial.begin(115200);
  delay(2000);

  // ==================================================
  // I2C INITIALIZATION
  // SDA = GPIO 21
  // SCL = GPIO 22
  // ==================================================

  Wire.begin(21, 22);

  // ==================================================
  // MPU6050 INITIALIZATION
  // ==================================================

  mpu.initialize();
  mpu.setSleepEnabled(false);

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully");
  }
  else {
    Serial.println("MPU6050 connection failed");
  }

  // ==================================================
  // WIFI CONNECTION
  // ==================================================

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");

  // ==================================================
  // THINGSPEAK INITIALIZATION
  // ==================================================

  ThingSpeak.begin(client);

  Serial.println("ThingSpeak Started");
}

void loop() {

  // ==================================================
  // READ MPU6050 ACCELERATION
  // ==================================================

  mpu.getAcceleration(&ax, &ay, &az);

  // ==================================================
  // GESTURE DETECTION
  // ==================================================

  if (ax > threshold) {

    // Right tilt
    gestureCode = 1;
  }

  else if (ax < -threshold) {

    // Left tilt
    gestureCode = 2;
  }

  else {

    // Device is stable
    gestureCode = 0;
  }

  // ==================================================
  // SERIAL MONITOR
  // ==================================================

  Serial.print("AX: ");
  Serial.print(ax);

  Serial.print(" | AY: ");
  Serial.print(ay);

  Serial.print(" | AZ: ");
  Serial.print(az);

  Serial.print(" | Gesture: ");
  Serial.println(gestureCode);

  // ==================================================
  // UPLOAD DATA TO THINGSPEAK
  // EVERY 15 SECONDS
  // ==================================================

  if (millis() - lastUpdate >= UPDATE_INTERVAL) {

    // Field 1 = X-axis acceleration
    ThingSpeak.setField(1, ax);

    // Field 2 = Y-axis acceleration
    ThingSpeak.setField(2, ay);

    // Field 3 = Gesture code
    ThingSpeak.setField(3, gestureCode);

    // Send data to ThingSpeak
    int status = ThingSpeak.writeFields(
      channelID,
      writeAPIKey
    );

    // ==================================================
    // CHECK UPLOAD STATUS
    // ==================================================

    if (status == 200) {

      Serial.println("Data uploaded to ThingSpeak successfully");
    }

    else {

      Serial.print("ThingSpeak upload failed. HTTP code: ");
      Serial.println(status);
    }

    lastUpdate = millis();
  }

  // Small delay
  delay(100);
}
