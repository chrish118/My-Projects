#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------- Pins ----------
#define DHTPIN 4
#define DHTTYPE DHT11
#define BUZZERPIN 25

// ---------- OLED ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool oledWorking = false;
float alertTemp = 35.0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Starting ESP32 Room Monitor...");

  pinMode(BUZZERPIN, OUTPUT);
  digitalWrite(BUZZERPIN, LOW);

  dht.begin();

  Wire.begin(21, 22);

  oledWorking = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);

  if (oledWorking) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("ESP32 Monitor");
    display.println("System started");
    display.display();
  } else {
    Serial.println("OLED not detected.");
  }

  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  Serial.println("------------------");

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT11 Error: check wiring");

    digitalWrite(BUZZERPIN, LOW);

    if (oledWorking) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("DHT11 ERROR");
      display.println("Check wiring");
      display.display();
    }

    delay(3000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  bool alert = temp >= alertTemp;

  if (alert) {
    digitalWrite(BUZZERPIN, HIGH);
    Serial.println("ALERT: Temperature high!");
  } else {
    digitalWrite(BUZZERPIN, LOW);
    Serial.println("Status: Normal");
  }

  if (oledWorking) {
    display.clearDisplay();

    display.setCursor(0, 0);
    display.println("Room Monitor");

    display.setCursor(0, 18);
    display.print("Temp: ");
    display.print(temp);
    display.println(" C");

    display.setCursor(0, 32);
    display.print("Hum: ");
    display.print(hum);
    display.println(" %");

    display.setCursor(0, 50);
    if (alert) {
      display.println("ALERT: HOT");
    } else {
      display.println("Status: OK");
    }

    display.display();
  }

  delay(2000);
}