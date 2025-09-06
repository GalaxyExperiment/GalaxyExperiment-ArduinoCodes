#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define Sens_Pin A0
double V_OLD_0_C = 690.0; // Forward voltage at 0°C in mV
double Temperature_Coefficient = -1.6; // mV change per °C
double VCC_Voltage = 5010.0; // Arduino VCC in mV

LiquidCrystal_I2C lcd(0x27, 16, 2); // If not working, try 0x3F

void setup() {
  pinMode(Sens_Pin, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  double V_NEW = analogRead(Sens_Pin) * VCC_Voltage / 1024.0;
  double Temperature = (V_NEW - V_OLD_0_C) / Temperature_Coefficient;
  double Fahrenheit = (Temperature * 9.0 / 5.0) + 32.0;

  Serial.print("Temp = ");
  Serial.print(Temperature);
  Serial.print(" °C, ");
  Serial.print(Fahrenheit);
  Serial.println(" °F");

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(Temperature);
  lcd.print(" ");
  lcd.write(223);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(Fahrenheit);
  lcd.print(" ");
  lcd.write(223);
  lcd.print("F   ");

  delay(500);
}
