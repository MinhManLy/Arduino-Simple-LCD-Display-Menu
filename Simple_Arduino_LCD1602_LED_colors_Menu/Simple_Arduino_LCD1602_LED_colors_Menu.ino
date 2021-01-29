/* Simple code for Arduino LCD1602 LED colors Menu
 * Project: None
 * Author: Minh Man Ly
 * Circuit schematic: Available on the website below (Github)
 * Web link: https://github.com/MinhManLy/Arduino-Simple-LCD-Display-Menu
 */

// =============================================================================================== //
// ===                                        LIBRARIES                                        === //
// =============================================================================================== //

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// =============================================================================================== //
// ===                              PINS & VARIABLES DECLARATION                               === //
// =============================================================================================== //

#define button A3
#define red 6
#define green 5
#define blue 3

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int Mode = 1;

byte customChar[8] = {  //creates the arrow 
  0b10000,
  0b11000,
  0b11100,
  0b11110,
  0b11110,
  0b11100,
  0b11000,
  0b10000
};

// =============================================================================================== //
// ===                                  FUNCTIONS DEFINITION                                   === //
// =============================================================================================== //

void arrow() {
  if (Mode == 1){
    lcd.setCursor(0,0);
    lcd.write((uint8_t)0);
  }
  else if (Mode == 2) {
    lcd.setCursor(8,0);
    lcd.write((uint8_t)0);
  }
  else if (Mode == 3) {
    lcd.setCursor(0,1);
    lcd.write((uint8_t)0);
  }
  else if (Mode == 4) {
    lcd.setCursor(8,1);
    lcd.write((uint8_t)0);
  }
}

void screen(){
  lcd.setCursor(1,0);
  lcd.print("Off");
  lcd.setCursor(9,0);
  lcd.print("Red");
  lcd.setCursor(1,1);
  lcd.print("Green");
  lcd.setCursor(9,1);
  lcd.print("Blue");
}

// =============================================================================================== //
// ===                                     INITIAL SETUPS                                      === //
// =============================================================================================== //

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  lcd.createChar(0, customChar); // arrow Char created
  Mode = 1;
  arrow();
  screen();
}

// =============================================================================================== //
// ===                                    MAIN PROGRAM LOOP                                    === //
// =============================================================================================== //

void loop() {
  if (!digitalRead(button)){ 
    delay(250);                        // delay to debounce switch
    Mode++;
    if(Mode > 4){
     lcd.clear();
     Mode = 1;
    }
    //lcd.clear();
    arrow();
    screen();
    switch (Mode) {
      case 1: {
        lcd.clear();
        arrow();
        screen();
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
        break;
      }
      case 2: {
        lcd.clear();
        arrow();
        screen();
        digitalWrite(red, HIGH);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
        break;
      }
      case 3: {
        lcd.clear();
        arrow();
        screen();
        digitalWrite(red, LOW);
        digitalWrite(green, HIGH);
        digitalWrite(blue, LOW);
        break;
      }
      case 4: {
        lcd.clear();
        arrow();
        screen();
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
        digitalWrite(blue, HIGH);
        break;
      }
    }
  }
}

// =============================================================================================== //
// ===                                  FUNCTIONS DEFINITION                                   === //
// =============================================================================================== //

/*
void menu() {
  if (!(digitalRead(button))){
    Mode = Mode + 1;
    if (Mode > 4) {
      Mode = 1;
    }
    Serial.print("modeSettings = ");
    Serial.println(Mode);
    lcd.clear();
    arrow();
    screen();
    delay(200);
  }
}
*/
