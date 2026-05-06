# Day 02 - OLED + Buzzer Integration

## Objective
Today I attempted to integrate:
- DHT11 sensor
- OLED display
- Buzzer
with the ESP32.

The goal was to create a room monitoring system displaying temperature and humidity while triggering an alert buzzer at high temperature.

---

## Components Used
- ESP32 Dev Module
- DHT11 sensor
- SSD1306 OLED display
- Active buzzer
- Breadboard
- Jumper wires

---

## Wiring Configuration

### DHT11
- VCC → 3.3V
- GND → GND
- DATA → GPIO 4

### OLED
- VCC → 3.3V
- GND → GND
- SDA → GPIO 21
- SCL → GPIO 22

### Buzzer
- Positive → GPIO 25
- Negative → GND

---

## What Worked
- ESP32 successfully uploaded code
- Serial monitor worked correctly
- DHT11 worked independently earlier
- GitHub repository updated successfully

---

## Issues Encountered
- OLED may not be functioning correctly
- ESP32 entered “Guru Meditation Error”
- DHT11 readings occasionally failed
- Possible wiring instability from jumper cables
- Possible bad OLED

---

## Observations
- Multiple components added simultaneously made debugging difficult
- Need to isolate and test components individually
- Breadboard wiring may need improvement

---

## Plan For Next Session
1. Test DHT11 independently
2. Test OLED independently
3. Verify OLED address and driver
4. Rebuild wiring cleanly
5. Reintegrate components step-by-step

---

## Updates 
- Issue with the OLED. Replaced and bought a new one.
- New OLED working perfectly fine
- HELLO message displayed correctly! 
---
## Next steps
Connect all the wiring and then test the 
- Buzzer
- OLED
- DHT11
---
## Updates
- OLED receiving feed but Temperature and Humidity data dissorted.
---
## Next steps 
- Reduced the number of characters ||| It works perfectly now
--- 
## Functional Testing
- Everything connect and powered. 
- OLED live and receiving feed from DHT11.
- Alert threshold set to 35°C, so no buzzer alert received.
---
### Buzzer Alert Test
---
The alert threshold was temporarily reduced to 33°C for testing.
A lighter was briefly brought near the DHT11 sensor to increase the detected temperature.

---

### Result
---
- Temperature increased successfully
- OLED updated alert status
- Buzzer activated correctly once threshold was exceeded
---
### Conclusion
---
Sensor-to-output logic chain functions correctly.

---
---