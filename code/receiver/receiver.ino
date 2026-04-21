#include "BluetoothSerial.h"

// Check if Bluetooth is properly configured in the board definitions
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Initialize Bluetooth Serial object
BluetoothSerial SerialBT;

// --- Motor Pin Definitions ---
// Using L298N Motor Driver connections
// Left Motor pins
#define IN1 26 // Direction pin 1
#define IN2 27 // Direction pin 2
// Right Motor pins
#define IN3 14 // Direction pin 3
#define IN4 12 // Direction pin 4

// Enable pins (for PWM speed control)
#define ENA 25 // Speed control for Left Motor
#define ENB 33 // Speed control for Right Motor

// Variable to store the incoming Bluetooth command
char command;

void setup() {
  // Initialize standard Serial monitor for debugging
  Serial.begin(115200);
  
  // Start Bluetooth service with a specific broadcast name
  // This is the name you will connect to from your phone/transmitter
  SerialBT.begin("ESP32_CAR"); 
  Serial.println("The device started, now you can pair it with bluetooth!");

  // Set motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // --- PWM Setup for Speed Control ---
  // Attach the enable pins to PWM channels
  ledcAttachPin(ENA, 0); // Assign ENA to channel 0
  ledcAttachPin(ENB, 1); // Assign ENB to channel 1

  // Configure the PWM channels (Channel, Frequency in Hz, Resolution in bits)
  ledcSetup(0, 5000, 8); // 8-bit resolution = 0 to 255
  ledcSetup(1, 5000, 8);

  // Set initial speed (200 out of 255)
  ledcWrite(0, 200); // Left Motor Speed
  ledcWrite(1, 200); // Right Motor Speed
}

void loop() {
  // Check if data is available to read from Bluetooth
  if (SerialBT.available()) {
    // Read the incoming character (command)
    command = SerialBT.read();
    
    // Print the command to Serial Monitor for debugging
    Serial.println(command);

    // --- Control Logic based on received Bluetooth command ---
    // The transmitter sends specific characters (F, B, L, R, S) 
    // to control the movement of the car.
    switch (command) {
      case 'F': forward(); break;   // Move Forward
      case 'B': backward(); break;  // Move Backward
      case 'L': left(); break;      // Turn Left
      case 'R': right(); break;     // Turn Right
      case 'S': stopCar(); break;   // Stop completely
    }
  }
}

// --- Movement Helper Functions ---

// Move both motors forward
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Move both motors backward
void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Turn Left: Left motor backwards (or stopped), Right motor forwards
void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Turn Right: Left motor forwards, Right motor backwards (or stopped)
void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Stop: Cut power to all directional pins
void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}