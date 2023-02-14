#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; 

void setup() {
  Serial.begin(115200);
  if (!bme.begin(0x76)) {
    Serial.println("Não foi possível inicializar o BME280");
    while (1);
  }
}

void loop() {
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float humidity = bme.readHumidity();

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Pressão: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(1000);
}