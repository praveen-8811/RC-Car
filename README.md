# ESP32 Robot Car

![ESP32](https://img.shields.io/badge/Platform-ESP32-blue.svg)
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen.svg)

## 🚀 Project Overview
This project involves building a remote-controlled vehicle powered by the ESP32 microcontroller, featuring custom control logic. 
- **What problem it solves:** Provides a flexible, robust platform for learning robotics, wireless communication, and embedded systems programming.
- **Why ESP32?:** The ESP32 offers built-in WiFi and Bluetooth capabilities, dual-core processing power, and plenty of GPIO pins for controlling motors and reading sensors, making it an ideal brain for a smart RC car.

## 🎯 Features
- Remote control via Bluetooth controller App / Transmitter
- Wireless communication capabilities using ESP32's built-in Bluetooth Classic
- Precise motor control, directional steering, and PWM speed adjustment
- Highly extensible for future sensor additions

## 🧠 System Architecture
The system consists of two main parts: the Controller and the Robot Car. The controller sends directional and speed commands wirelessly via Bluetooth to the ESP32 on the car. The ESP32 processes these commands and sends PWM signals to the motor driver, which in turn drives the DC motors to move the car.

## 🔌 Hardware Components
- **ESP32 Microcontroller** (The brain of the car)
- **L298N Motor Driver** (Controls power delivery to the motors)
- **DC Motors** with Gearboxes & Wheels (For movement)
- **Robot Car Chassis kit** (Physical structure)
- **Battery Pack & Power Module** (Provides power to the ESP32 and Motors)

## ⚙️ Software Requirements
- **Arduino IDE** (or PlatformIO)
- ESP32 Board Package installed in Arduino IDE
- `BluetoothSerial.h` (Built-in ESP32 library for Bluetooth communication)

## 📡 Communication Details
The core of this project uses wireless communication to send commands from the remote to the car.

- **Protocol used:** Bluetooth Classic (Serial Port Profile - SPP)
- **Data format:** Single ASCII characters sent over serial (e.g., `'F'` for Forward, `'B'` for Backward, `'S'` for Stop).
- **Range:** ~10 meters (standard Bluetooth range), heavily dependent on obstacles and interference.
- **How data is processed:** The ESP32 constantly polls the Bluetooth serial buffer. When a valid character is received, it triggers a `switch` statement that executes the corresponding motor movement function.

## 📲 How to Run
Follow these step-by-step instructions to get the code running:

1. **Clone this repository:** `git clone https://github.com/praveen-8811/RC-Car.git`
2. **Open the code:** Navigate to `code/receiver/` and open `receiver.ino` using the Arduino IDE.
3. **Select your Board:** Select your specific **ESP32 Dev Module** and the correct **COM port** under the Tools menu.
4. **Upload:** Click **Upload** to flash the code to your ESP32 microcontroller.
5. **Connect:** Use a Bluetooth Serial App on your phone to connect to the device named `"ESP32_CAR"`.

## 🎮 Controls
- **F / Forward:** Both motors spin forward.
- **B / Backward:** Both motors spin in reverse.
- **L / Left:** Right motor spins forward, left motor spins backward (or stops) to turn left.
- **R / Right:** Left motor spins forward, right motor spins backward (or stops) to turn right.
- **S / Stop:** Cuts power to all directional pins.

## 📸 Output / Demo
Here is the robot car in action!

![Robot Car - Image 1](assets/images/img_1.jpeg)
![Robot Car - Circuit](assets/images/ckt_1.jpeg)

*(Check out `demo.mp4` and `vid_2.mp4` in the `assets/` folder for full video demonstrations!)*

## 🧠 Future Improvements
Looking forward, there are several ways this project can be enhanced:
- **Mobile App Control:** Building a custom React Native or Flutter app with a better UI.
- **Camera Integration:** Using an ESP32-CAM module for real-time FPV (First Person View) video streaming.
- **Obstacle Detection:** Adding Ultrasonic (HC-SR04) or IR sensors to prevent collisions automatically.
- **Voice Control:** Implementing voice isolation and recognition to drive the car with spoken commands.

## 🐞 Issues & Known Bugs
- **Delay in response:** There can sometimes be a slight input lag due to Bluetooth serial buffer processing.
- **Signal interference:** Standard 2.4GHz interference (from WiFi routers, etc.) can occasionally cause command drops.
- **Power draw drops:** If the battery is low, the L298N may not supply enough voltage for sudden direction changes.

## 🤝 Contribution
Contributions are welcome! Feel free to open issues or pull requests if you want to improve the code, fix bugs, or add new features.

## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
*Detailed project documentation, including schematics and design choices, can be found in `docs/report.pdf`.*
