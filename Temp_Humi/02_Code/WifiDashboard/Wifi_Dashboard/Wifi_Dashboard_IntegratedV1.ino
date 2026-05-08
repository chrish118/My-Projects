#include <WiFi.h>
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------- WIFI DETAILS --------
const char* ssid = "Sweeter-family";
const char* password = "ja@WL40099748123";

// -------- DHT11 --------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// -------- BUZZER --------
#define BUZZERPIN 25

// -------- OLED --------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------- WEB SERVER --------
WiFiServer server(80);

// -------- ALERT TEMP --------
float alertTemp = 35.0;

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(BUZZERPIN, OUTPUT);
  digitalWrite(BUZZERPIN, LOW);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED NOT FOUND");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Connecting WiFi...");
  display.display();

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  display.clearDisplay();
  display.setCursor(0, 10);
  display.println("WiFi Connected!");
  display.setCursor(0, 30);
  display.print("IP:");
  display.println(WiFi.localIP());
  display.display();

  server.begin();

  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  bool sensorOK = !(isnan(temp) || isnan(hum));
  bool alert = false;

  String tempText;
  String humText;
  String statusText;
  String statusColor;

  if (!sensorOK) {
    tempText = "Error";
    humText = "Error";
    statusText = "SENSOR ERROR";
    statusColor = "#ff4d4d";

    digitalWrite(BUZZERPIN, LOW);

    Serial.println("DHT11 Error");

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.println("DHT ERR");
    display.display();
  } 
  else {
    tempText = String(temp, 1);
    humText = String(hum, 0);

    alert = temp >= alertTemp;

    if (alert) {
      statusText = "HOT ALERT";
      statusColor = "#ff4d4d";
      digitalWrite(BUZZERPIN, HIGH);
    } 
    else {
      statusText = "NORMAL";
      statusColor = "#00ffcc";
      digitalWrite(BUZZERPIN, LOW);
    }

    Serial.print("Temp: ");
    Serial.print(tempText);
    Serial.print(" C | Humidity: ");
    Serial.print(humText);
    Serial.print(" % | Status: ");
    Serial.println(statusText);

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("T:");
    display.print(temp, 1);

    display.setCursor(0, 24);
    display.print("H:");
    display.print(hum, 0);
    display.print("%");

    display.setTextSize(1);
    display.setCursor(0, 52);

    if (alert) {
      display.print("HOT ALERT");
    } else {
      display.print("OK");
    }

    display.display();
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client Connected");

    String webpage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Dashboard</title>
  <meta http-equiv="refresh" content="2">

  <style>
    body {
      background-color: #111;
      color: white;
      font-family: Arial;
      text-align: center;
      padding-top: 50px;
    }

    .card {
      background: #222;
      width: 350px;
      margin: auto;
      padding: 30px;
      border-radius: 20px;
      box-shadow: 0px 0px 20px rgba(0,255,200,0.3);
    }

    h1 {
      color: #00ffcc;
      margin-bottom: 25px;
    }

    .reading {
      font-size: 24px;
      margin: 15px;
    }

    .status {
      color: STATUS_COLOR;
      font-weight: bold;
      font-size: 28px;
      margin-top: 25px;
    }
  </style>
</head>

<body>
  <div class="card">
    <h1>ESP32 Dashboard</h1>

    <div class="reading">
      Temperature: TEMP_VALUE C
    </div>

    <div class="reading">
      Humidity: HUM_VALUE %
    </div>

    <div class="status">
      STATUS_VALUE
    </div>
  </div>
</body>
</html>
)rawliteral";

    webpage.replace("TEMP_VALUE", tempText);
    webpage.replace("HUM_VALUE", humText);
    webpage.replace("STATUS_VALUE", statusText);
    webpage.replace("STATUS_COLOR", statusColor);

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    client.print(webpage);

    delay(1);
    client.stop();

    Serial.println("Client Disconnected");
  }

  delay(100);
}