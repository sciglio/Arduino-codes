//Live level plot on LCD display
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 12 // what digital pin we're connected to
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

int minutes;
int i;
float Temp;
float Hum;
float avTempHour;
float avHumHour;
float avTempMin;
float avHumMin;

const int buttonPin=2;
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
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT);
  
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
  lcd.setBacklight(50);
  lcd.setCursor(6,0);
  lcd.print("Welcome!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LUMI AMBIENT CONTROL");
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
  for(minutes=0, avTempHour=0.0, avHumHour=0.0; minutes<60; minutes++)
  {
    for(i=0, avTempMin=0.0, avHumMin=0.0; i<20; i++)
    {
  
  
      Temp=dht.readTemperature();
      avTempMin+=Temp;
      Serial.println(Temp);
      lcd.setCursor(0,0);
      lcd.print("Temperature  T=");
      lcd.print(Temp);
      lcd.setCursor(19,0);
      lcd.print("C"); 
    
      Hum=dht.readHumidity();
      avHumMin+=Hum;
      Serial.println(Hum);
      lcd.setCursor(0,2);
      lcd.print("Humidity     H=");
      lcd.print(Hum);
      lcd.setCursor(19,2);
      lcd.print("%");
    
  
  
      lcd.setCursor(i,1);
      if (Temp <22.0 && Temp>18.0)
        lcd.write(byte(3));
      else if (Temp <24.0 && Temp>22.1)
        lcd.write(byte(4));
      else if (Temp <26 && Temp>24.1)
        lcd.write(byte(5));
      else if (Temp <28 && Temp>26.1)
        lcd.write(byte(6));
      else if (Temp>28.1)
        lcd.write(byte(7));
      else if (Temp <17.9 && Temp>15)
        lcd.write(byte(2));
      else if (Temp <14.9 && Temp>13)
        lcd.write(byte(1));
      else if (Temp <12.9)
        lcd.write(byte(0));
        
      
  
      lcd.setCursor(i,3);
      if (Hum <=60 && Hum>=40)
        lcd.write(byte(3));
      else if (Hum <=70 && Hum>=60.1)
        lcd.write(byte(4));
      else if (Hum <=80 && Hum>=70.1)
        lcd.write(byte(5));
      else if (Hum <=90 && Hum>=80.1)
        lcd.write(byte(6));
      else if (Hum <=100 && Hum>=90.1)
        lcd.write(byte(7));
      else if (Hum <=39.9 && Hum>=30)
        lcd.write(byte(2));
      else if (Hum <=29.9 && Hum>=20)
        lcd.write(byte(1));
      else if (Hum <=19.9 && Hum>=0)
        lcd.write(byte(0));
       delay(3000);
       buttonState=digitalRead(buttonPin);

 if (buttonState!=lastButtonState)
 {
    if (buttonState==HIGH)
    {
      buttonPushCounter++;
    }

    delay(50);
 }

lastButtonState=buttonState;

 if(buttonPushCounter%2==0)
 {
     lcd.setBacklight(50);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
 }
 else
 {
     lcd.setBacklight(0);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
 }
    }
    lcd.clear();
    avTempMin=avTempMin/20;
    lcd.setCursor(0,0);
    lcd.print("Last 3 minutes:");
    lcd.setCursor(0,1);
    lcd.print("T_mean=");
    lcd.print(avTempMin);
    lcd.setCursor(11,1);
    lcd.print("C"); 
  
    avHumMin=avHumMin/20;
    lcd.setCursor(0,2);
    lcd.print("H_mean=");
    lcd.print(avHumMin);
    lcd.setCursor(11,2);
    lcd.print("%");
    delay(5000);
    lcd.clear();
  }
  
    
  
}
