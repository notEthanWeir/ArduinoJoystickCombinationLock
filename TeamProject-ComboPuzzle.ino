// Setup pins for Joystick ( X-Axis, Y-Axis, Switch)
int swPin = 6;
int xPin = A0;
int yPin = A1;

// Variables to hold the initial reads from the Joystick
int xRead;
int yRead;

// Variables to further debug joystick issues
int swRead;
int upVal;
int sideVal;

// String to save the current code input attempt
String myString = "";

// Library for ease of LCD Screen use
#include <LiquidCrystal.h>

// Pin Setup for the LCDs
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:

  // Serial for Debugging
  Serial.begin(9600);

  // LCD Setup 
  lcd.begin(16,2);
  lcd.setCursor(0,0);

  // Initial Screen Display State
  lcd.print("Please Enter");
  lcd.setCursor(0,1);
  lcd.print("The Combination");

  // Initializing the switch and joystick pins
  pinMode(swPin,INPUT_PULLUP);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Read both axis and switch to get a baseline reading and then map the values to more manageable numbers
  yRead = analogRead(yPin);
  xRead = analogRead(xPin);
  swRead = digitalRead(swPin);
  upVal = map(yRead, 0, 1023, 1, 10);
  sideVal = map(xRead, 0, 1023, 1, 10);


  Serial.println(swRead);

  // Read Joystick and add the according direction as a string to the combination attempt string
  if (upVal >= 8) {
    delay(500);
    myString.concat("up");
  }
  else if (upVal <= 1) {
    delay(500);
    myString.concat("down");
  }
  else if (sideVal >= 8) {
    delay(500);
    myString.concat("left");
  }
  else if (sideVal <= 1) {
    delay(500);
    myString.concat("right");
  }
  
  // ON CLICK check code attempt to Match the Correct combo, after screen readout of correct or invalid restart system.

  if (swRead == 0) {
    if(myString == "upupdowndownleftrightleftright") {
        delay(50);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Congrats!");
        delay(5000);

        myString.remove(0);

        lcd.begin(16,2);
        lcd.setCursor(0,0);
        lcd.print("Please Enter");
        lcd.setCursor(0,1);
        lcd.print("The Combination");
    }
    else {
      delay(50);
      lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Code Invalid");
        lcd.setCursor(0,1);
        lcd.print("Try Again");
        delay(5000);

        myString.remove(0);

        lcd.begin(16,2);
        lcd.setCursor(0,0);
        lcd.print("Please Enter");
        lcd.setCursor(0,1);
        lcd.print("The Combination");
    }
  }
}