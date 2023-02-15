#include <DHT.h>
#include <Adafruit_BMP085.h>

#define BLYNK_TEMPLATE_ID "TMPLK4OfRcOw"
#define BLYNK_DEVICE_NAME "Weather Station"
#define BLYNK_AUTH_TOKEN "XkG9OGWCzahgUAYI985FUO0Wz68rKGVs"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

const char* auth = BLYNK_AUTH_TOKEN;
const char* ssid = "TP-Link_FFBC";
const char* password = "sorriso0";

#define LDR 33
#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);

  dht.begin();
  bmp.begin();
  pinMode(LDR, INPUT);
}

void loop() {
  Blynk.virtualWrite(V0, dht.readTemperature());
  Blynk.virtualWrite(V1, dht.readHumidity());
  Blynk.virtualWrite(V2, 100.0*analogRead(LDR)/4096.0);
  Blynk.virtualWrite(V3, bmp.readPressure());
  delay(1000);
}