//Live level plot on LCD display
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display
const int buttonPin=2;
int i;
int buttonPushCounter=0;
int buttonState=0;
int lastButtonState=0;


// make some custom characters:
byte zero[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111
};

byte one[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111
};

byte two[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111
};

byte three[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte four[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte five[8] = {
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte six[8] = {
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte seven[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};


void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

  lcd.init();                      // initialize the lcd 

  // create a new character
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);
  lcd.createChar(6, six);
  lcd.createChar(7, seven);
  // Print a message to the LCD.
  lcd.setBacklight(1);
  lcd.setCursor(6,0);
  lcd.print("Welcome!");
  delay(2000);
  lcd.setCursor(7,2);
  lcd.print("Info:");
  lcd.setCursor(0,3);
  lcd.print("scmarco@chalmers.se");
  delay(3000);
  lcd.clear();
 }
void loop()
{
 buttonState=digitalRead(buttonPin);

 if (buttonState!=lastButtonState)
 {
    if (buttonState==HIGH)
    {
      buttonPushCounter++;
      lcd.setCursor(0,0);
      lcd.print("Button pushed:");
      lcd.setCursor(0,1);
      lcd.print(buttonPushCounter);
    }

    delay(50);
 }

lastButtonState=buttonState;

 if(buttonPushCounter%2==0)
 {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
 }
 else
 {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
 }
 
     
  
}
