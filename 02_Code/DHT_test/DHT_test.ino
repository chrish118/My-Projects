#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Error reading sensor!");
    delay(2000);
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C | Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  delay(2000);
}