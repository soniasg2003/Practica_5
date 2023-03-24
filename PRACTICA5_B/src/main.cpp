#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_SPACE_SYMBOL 0x20 //space symbol from LCD ROM, see p.9 of GDM2004D datasheet
 
LiquidCrystal_I2C lcd_01(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE); //all three address pads on the PCF8574 shield are open
LiquidCrystal_I2C lcd_02(PCF8574_ADDR_A20_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE); //all three address pads on the PCF8574 shield are shorted
 

void setup()
{
  Serial.begin(115200);

  while (lcd_01.begin(16, 2) != 1) //lcd1: colums - 20, rows - 4, lcd2: colums - 16, rows - 2
  {
    Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
    delay(5000);
  }
while (lcd_02.begin(20, 4) != 1) //lcd1: colums - 20, rows - 4, lcd2: colums - 16, rows - 2
  {
    Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
    delay(5000);
  }


  lcd_01.print(F("PCF8574_01 is OK...")); //(F()) saves string to flash & keeps dynamic memory free
  lcd_02.print(F("PCF8574_02 is OK..."));
  delay(2000);

  lcd_01.clear();
  lcd_02.clear();

  /* prints static text */
  lcd_01.setCursor(0, 0);                 //set 1-st colum & 2-nd row, 1-st colum & row started at zero
  lcd_01.print(F("LCD1 Hello world"));
  lcd_01.setCursor(0, 2);
  lcd_01.print(F("Random number:"));

  lcd_02.setCursor(0, 0);
  lcd_02.print(F("LCD2 Hello world"));
  lcd_02.setCursor(0, 1);
  lcd_02.print(F("Random number:"));
}

void loop()
{
  /* prints dynamic text */
  lcd_01.setCursor(14, 2);                //set 15-th colum & 3-rd  row, 1-st colum & row started at zero
  lcd_01.print(random(10, 1000));
  lcd_01.write(LCD_SPACE_SYMBOL);

  lcd_02.setCursor(14, 1);                //set 15-th colum & 2-rd  row, 1-st colum & row started at zero
  lcd_02.print(random(10, 1000));
  lcd_02.write(LCD_SPACE_SYMBOL);

  delay(1000);
}