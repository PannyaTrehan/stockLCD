#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Check if data is available to read from the serial port
  if (Serial.available() > 0) {
    // Read the incoming data as a string
    String incomingString = Serial.readStringUntil('\n');

    // Clear the LCD
    lcd.clear();

    // Find the position of the comma in the string
    int commaPosition = incomingString.indexOf(',');

    // If a comma is found
    if (commaPosition != -1) {
      // Display the part before the comma on the first line
      lcd.setCursor(0, 0);
      lcd.print(incomingString.substring(0, commaPosition));

      // Display the part after the comma on the second line
      lcd.setCursor(0, 1);
      lcd.print(incomingString.substring(commaPosition + 1));

      // Print the received string to the Serial Monitor for verification
      Serial.println("Received: " + incomingString);
    } else {
      // If no comma is found, display the entire string on the first line
      lcd.print(incomingString);

      // Print the received string to the Serial Monitor for verification
      Serial.println("Received: " + incomingString);
    }
  }
}
