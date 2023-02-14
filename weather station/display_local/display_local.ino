#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define LDR 33
#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();

  dht.begin();
}

void loop() {
  lcd.setCursor(0, 0);

  lcd.print("Luz:");
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
  int atm = 1;
  lcd.print(atm);
  lcd.print("atm");

  delay(1000);
}