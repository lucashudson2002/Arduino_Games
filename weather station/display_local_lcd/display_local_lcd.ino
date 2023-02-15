#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

#define LDR 33
#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

Adafruit_BMP085 bmp;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();

  dht.begin();

  bmp.begin();
}

void loop() {
  lcd.setCursor(0, 0);

  lcd.print("Lum:");
  int ldr = analogRead(LDR);
  ldr = 100.0*ldr/4096.0;
  lcd.print(ldr);
  lcd.print("% ");

  lcd.print("Tem:");
  int temp = dht.readTemperature();
  lcd.print(temp);
  lcd.print("oC");

  lcd.setCursor(0, 1);

  lcd.print("Hum:");
  int hum = dht.readHumidity();
  lcd.print(hum);
  lcd.print("% ");

  lcd.print("Atm:");
  float atm = bmp.readPressure()/101325.0;
  lcd.print(atm);

  delay(1000);
}