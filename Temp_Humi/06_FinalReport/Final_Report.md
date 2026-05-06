# ESP32 Room Monitoring System – Final Report

## 1. Introduction

This project involved designing and developing a real-time environmental monitoring system using the ESP32 microcontroller. The system was capable of measuring room temperature and humidity using a DHT11 sensor, displaying the readings on an OLED display, and activating a buzzer alert whenever the temperature exceeded a predefined threshold.

The project was developed as part of a hands-on embedded systems learning process with a focus on:

* Sensor integration
* Embedded C++ programming
* Hardware debugging
* I2C communication
* Real-time monitoring systems
* Structured project documentation

The project also served as an introduction to modular debugging and engineering workflow practices using GitHub for version control and documentation.

---

## 2. Objectives

The main objectives of the project were:

* Measure live temperature using a DHT11 sensor
* Measure live humidity using a DHT11 sensor
* Display readings on an SSD1306 OLED display
* Trigger a buzzer alert when temperature exceeds a threshold
* Display sensor information through the Serial Monitor
* Learn ESP32 hardware interfacing and debugging techniques
* Understand I2C communication between devices
* Organize project development using GitHub and structured folders

---

## 3. Components Used

| Component            | Purpose                          |
| -------------------- | -------------------------------- |
| ESP32 Dev Module     | Main microcontroller             |
| DHT11 Sensor         | Temperature and humidity sensing |
| SSD1306 OLED Display | Real-time visual output          |
| Active Buzzer        | Alert system                     |
| Breadboard           | Circuit prototyping              |
| Jumper Wires         | Electrical connections           |
| USB Cable            | Power and programming            |

---

## 4. System Overview

The ESP32 acts as the main controller of the system.

The DHT11 sensor continuously measures environmental temperature and humidity values. These readings are processed by the ESP32 and displayed on the OLED screen using I2C communication.

If the measured temperature exceeds the predefined threshold value, the ESP32 activates the buzzer to provide an audible warning.

The system also outputs all readings to the Arduino Serial Monitor for debugging and testing purposes.

---

## 5. Wiring Configuration

## DHT11 Sensor

| DHT11 Pin | ESP32 Connection |
| --------- | ---------------- |
| VCC       | 3.3V             |
| GND       | GND              |
| DATA      | GPIO 4           |

---

## SSD1306 OLED Display

| OLED Pin | ESP32 Connection |
| -------- | ---------------- |
| VCC      | 3.3V             |
| GND      | GND              |
| SDA      | GPIO 21          |
| SCL      | GPIO 22          |

---

## Buzzer

| Buzzer Pin | ESP32 Connection |
| ---------- | ---------------- |
| Positive   | GPIO 25          |
| Negative   | GND              |

---

## 6. Software and Libraries Used

## Software

* Arduino IDE
* Visual Studio Code
* GitHub

## Libraries

| Library            | Purpose                     |
| ------------------ | --------------------------- |
| DHT.h              | Reading DHT11 sensor values |
| Wire.h             | I2C communication           |
| Adafruit_GFX.h     | Graphics support for OLED   |
| Adafruit_SSD1306.h | OLED display control        |

---

## 7. Understanding I2C Communication

The OLED display communicates with the ESP32 using the I2C communication protocol.

I2C uses only two communication lines:

| Line | Function   |
| ---- | ---------- |
| SDA  | Data line  |
| SCL  | Clock line |

In this project:

* SDA was connected to GPIO 21
* SCL was connected to GPIO 22

The ESP32 acts as the “master” device while the OLED acts as a “slave” device.

Each I2C device has a unique address. The OLED display used the address:

0x3C

This allowed the ESP32 to correctly identify and communicate with the OLED display.

---

## 8. Program Logic

The system follows the following operational sequence:

1. Initialize Serial Monitor
2. Initialize DHT11 sensor
3. Initialize OLED display
4. Read temperature and humidity values
5. Display readings on OLED
6. Print readings to Serial Monitor
7. Compare temperature with alert threshold
8. Activate buzzer if threshold exceeded
9. Repeat continuously

---

## 9. Challenges Encountered

Several challenges were faced during development.

## 9.1 Faulty OLED Module

The original OLED display behaved inconsistently and caused repeated system instability.

### Symptoms:

* Display turning blank
* ESP32 watchdog crashes
* Random display behavior

### Solution:

The OLED module was replaced with a new SSD1306 display, which solved the issue.

---

## 9.2 Wiring Instability

Initial breadboard wiring caused unstable connections.

### Solution:

* Rewired the system cleanly
* Used direct ESP32 connections for OLED testing
* Improved jumper wire organization

---

## 9.3 OLED Text Distortion

Long text strings caused cramped and distorted OLED output.

### Solution:

* Simplified the user interface
* Reduced text size and spacing
* Used shorter labels such as:

  * T:
  * H:
  * OK
  * HOT!

---

## 9.4 Sensor Debugging

The DHT11 occasionally failed to return readings.

### Solution:

* Used Serial Monitor for debugging
* Added sensor error handling using isnan()
* Tested components independently before integration

---

## 10. Testing and Results

## OLED Display Test

Result: PASS

* OLED initialized correctly
* Text displayed successfully
* Stable operation confirmed

---

## DHT11 Sensor Test

Result: PASS

* Temperature readings updated correctly
* Humidity readings updated correctly
* Stable sensor readings observed

---

## Buzzer Alert Test

Result: PASS

### Method

The alert threshold was temporarily reduced to 33°C.
A lighter was briefly brought near the DHT11 sensor.

### Result

* Temperature increased successfully
* OLED displayed alert condition
* Buzzer activated correctly

This confirmed successful sensor-to-output logic.

---

## Serial Monitor Test

Result: PASS

* Sensor data displayed correctly
* Continuous readings confirmed
* No communication issues detected

---

## 11. Final Output

The final system successfully:

* Measured room temperature
* Measured room humidity
* Displayed data on OLED
* Triggered buzzer alerts during high temperatures
* Displayed live readings in Serial Monitor

The project demonstrated stable embedded system operation and successful integration of multiple hardware components.

---

## 12. Skills Learned

During this project, the following technical skills were developed:

## Hardware Skills

* Breadboard prototyping
* ESP32 wiring
* Sensor integration
* OLED interfacing
* Debugging hardware faults

## Programming Skills

* Embedded C++ programming
* Arduino IDE workflow
* GPIO control
* Conditional logic
* Serial debugging
* Modular coding

## Embedded Systems Concepts

* I2C communication
* Sensor-to-output workflow
* Real-time monitoring systems
* Hardware/software integration

## Engineering Workflow Skills

* GitHub version control
* Documentation practices
* Testing methodology
* Structured debugging workflow

---

## 13. Future Improvements

Several future upgrades can improve the project further.

## Possible Improvements

* ESP32 WiFi dashboard
* Mobile monitoring interface
* Cloud data logging
* TFT graphical display
* Data storage using SD card
* Push notifications
* Multiple sensor integration
* Battery-powered operation

---

## 14. Conclusion

The ESP32 Room Monitoring System was successfully designed, built, tested, and documented.

The project provided practical experience in embedded systems engineering, sensor communication, hardware debugging, and real-time monitoring systems.

The system operated reliably and successfully demonstrated the interaction between sensors, processing logic, displays, and output devices.

In addition to technical implementation, the project also highlighted the importance of modular debugging, documentation, and structured engineering workflow.

Overall, the project achieved all initial objectives and created a strong foundation for future ESP32 and IoT-based developments.
