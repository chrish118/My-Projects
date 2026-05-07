#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define BUZZERPIN 25

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float alertTemp = 33.0;

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(BUZZERPIN, OUTPUT);
  digitalWrite(BUZZERPIN, LOW);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED NOT FOUND");
    while (true)
      ;
  }

  display.clearDisplay();
  display.display();
  delay(500);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT ERROR");
    digitalWrite(BUZZERPIN, LOW);

    display.setTextSize(2);
    display.setCursor(0, 20);
    display.println("DHT ERR");
    display.display();

    delay(2000);
    return;
  }

  bool alert = temp >= alertTemp;
  digitalWrite(BUZZERPIN, alert ? HIGH : LOW);

  Serial.print("Temp: ");
  Serial.print(temp, 1);
  Serial.print(" C | Humidity: ");
  Serial.print(hum, 0);
  Serial.println(" %");

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("T:");
  display.print(temp, 1);
  display.write(247);
  display.print("C");

  display.setCursor(0, 24);
  display.print("H:");
  display.print(hum, 0);
  display.print("%");

  display.setTextSize(1);
  display.setCursor(0, 52);
  if (alert) {
    display.print("ALERT HOT");
  } else {
    display.print("Normal");
  }

  display.display();

  delay(2000);
}