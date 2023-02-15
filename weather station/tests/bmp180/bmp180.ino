#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void setup() {
  Wire.begin();

  Serial.begin(115200);

  if (!bmp.begin()) 
  {
    Serial.println("Sensor BMP085 nao encontrado, verifique as conexoes!");
    while (1) {}
  }
}

void loop() {
  Serial.print("Pressao = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  delay(1000);
}