#include <Wire.h>
#include <MicroLCD.h>

//LCD_SH1106 lcd;
LCD_SSD1306 lcd;

void setup()
{
	lcd.begin();
}

void loop()
{
  lcd.clear();
  lcd.setFontSize(FONT_SIZE_SMALL);
  lcd.println("Ola, Mundo!");
  lcd.setFontSize(FONT_SIZE_MEDIUM);
  lcd.println("Ola, Mundo!");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setFontSize(FONT_SIZE_SMALL);
  lcd.printLong(12345678);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setFontSize(FONT_SIZE_MEDIUM);
  lcd.printLong(12345678);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setFontSize(FONT_SIZE_LARGE);
  lcd.printLong(12345678);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setFontSize(FONT_SIZE_XLARGE);
  lcd.printLong(12345678);
  delay(1000);
}

