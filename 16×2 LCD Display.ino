#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Change the address if your scanner showed a different address
LiquidCrystal_I2C lcd(0x20, 16, 2);

void setup() {
  lcd.init();          // Initialize LCD
  lcd.backlight();     // Turn ON backlight
  lcd.clear();

  // Display name on first line
  lcd.setCursor(0, 0);   // Column 0, Row 0
  lcd.print("Home Revise");

  // Optional second line
  lcd.setCursor(0, 1);   // Column 0, Row 1
  lcd.print("Study Make Easy");
}

void loop() {		 // Nothing needed
}
