# Testing Results

## OLED Display Test
Result: PASS

- OLED initialized successfully
- Text displayed correctly
- Stable operation confirmed

---

## DHT11 Sensor Test
Result: PASS

- Temperature readings updated correctly
- Humidity readings updated correctly
- No sensor disconnects observed

---

## Buzzer Alert Test
Result: PASS

### Method
Alert threshold temporarily reduced to 33°C.
Heat applied near DHT11 sensor using lighter.

### Result
- Temperature increased successfully
- OLED updated correctly
- Buzzer activated as expected

---

## Serial Monitor Test
Result: PASS

- Live readings displayed correctly
- No communication issues detected

---

## Issues Encountered

### Faulty OLED Module
- Original OLED behaved inconsistently
- Replaced with new SSD1306 OLED module

### OLED Text Overlap
- Long text caused distortion
- UI redesigned using shorter labels

### Wiring Stability
- Breadboard rail setup caused instability
- Direct ESP32 wiring improved reliability