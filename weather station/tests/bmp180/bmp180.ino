#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup() {
  Serial.begin(115200);
  if (!bmp.begin()) {
    Serial.println("Não foi possível inicializar o BMP180");
    while (1);
  }
}

void loop() {
  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure) {
    Serial.print("Pressão atmosférica: ");
    Serial.print(event.pressure);
    Serial.println(" Pa");
  } else {
    Serial.println("Não foi possível ler a pressão");
  }

  delay(1000);
}