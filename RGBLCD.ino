#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TCS34725.h"
#include <LiquidCrystal_I2C.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  if (!tcs.begin()) {
    Serial.println("Could not find a valid TCS34725 sensor, check wiring!");
    while (1);
  }

  lcd.begin(16, 2);
  lcd.backlight();
}

void loop() {

  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);

  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R:"); lcd.print(r);
  lcd.setCursor(5, 0);
  lcd.print("G:"); lcd.print(g);
  lcd.setCursor(10, 0);
  lcd.print("B:"); lcd.print(b);

  if (uang20000(r, g, b)) {
    lcd.setCursor(0,1);
    lcd.print("Uang 20000");
  }  else if (uang50000(r, g, b)) {
    lcd.setCursor(0,1);
    lcd.print("Uang 50000");
  } else if (uang100000(r, g, b)) {
    lcd.setCursor(0,1);
    lcd.print("Uang 100000");
  } else {
    lcd.setCursor(0,1);
    lcd.print("Error");
  }
  delay(500);

}

bool uang20000(uint16_t r, uint16_t g, uint16_t b) {
  return (r < 250 && g > 250 && b < 200);
}

bool uang50000(uint16_t r, uint16_t g, uint16_t b) {
  return (r < 250 && g > 250 && b > 200);
}

bool uang100000(uint16_t r, uint16_t g, uint16_t b) {
  return (r > 400 && g < 400 && b < 300);
}
