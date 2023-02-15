#include <Wire.h>
#include <MicroLCD.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

#define LDR 33
#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

Adafruit_BMP085 bmp;

LCD_SSD1306 lcd;

void setup() {
  lcd.begin();
  lcd.setFontSize(FONT_SIZE_MEDIUM);

  dht.begin();

  bmp.begin();
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("Luminosity:");
  int ldr = analogRead(LDR);
  ldr = 100.0*ldr/4096.0;
  lcd.print(ldr);
  lcd.println("%");

  lcd.print("Temp:");
  int temp = dht.readTemperature();
  lcd.print(temp);
  lcd.println("oC");

  lcd.print("Humidity:");
  int hum = dht.readHumidity();
  lcd.print(hum);
  lcd.println("%");

  lcd.print("Atm:");
  int atm = bmp.readPressure();
  lcd.print(atm);
  lcd.println("Pa");

  delay(2000);
}