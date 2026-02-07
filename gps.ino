#include <TinyGPSPlus.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
  const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //RS, E, D4, D5, D6, D7

  byte North[] = {
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    B00100,
    B00100,
    B00100
  };
  byte South[] = {
    B00100,
    B00100,
    B00100,
    B00100,
    B00100,
    B11111,
    B01110,
    B00100
  };
  byte West[] ={
    B00001,
    B00011,
    B00111,
    B01111,
    B01111,
    B00111,
    B00011,
    B00001
  };
  byte East[] ={
    B10000,
    B11000,
    B11100,
    B11110,
    B11110,
    B11100,
    B11000,
    B10000,
  };


// Define RX and TX pins for SoftwareSerial
#define RXPin 8
#define TXPin 9
#define GPSBaud 9600

SoftwareSerial gpsSerial(RXPin, TXPin);
TinyGPSPlus gps;

double LocationOneLat = 39.78290;
double LocationOneLong = -84.06158;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);// For the serial monitor
  lcd.begin(16,2);
  gpsSerial.begin(GPSBaud);
  lcd.createChar(1,North);
  lcd.createChar(2,South);
  lcd.createChar(3,East);
  lcd.createChar(0,West);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  while (gpsSerial.available() > 0){
    if (gps.encode(gpsSerial.read())) {
      // 1. Check if GPS has a fix on a satellite
      if (!gps.location.isValid()) { 
          lcd.setCursor(0,0);
        lcd.setCursor(0,0); 
        lcd.print("Waiting for GPS"); 
      return;
      }

      // Storing our current position
      double current_lat = gps.location.lat();
      double current_long = gps.location.lng();

      // Finding the distance between our current location and destination.
      double Distance = TinyGPSPlus::distanceBetween(
        current_lat, current_long, 
        LocationOneLat, LocationOneLong 
      );
      double Course = TinyGPSPlus::courseTo(
        current_lat, current_long, 
        LocationOneLat, LocationOneLong 
      );
      const char* Cardinal = TinyGPSPlus::cardinal(Course);
      Serial.write(Cardinal);
     
      // Printing the distance to the LCD
      lcd.setCursor(0,0);
      lcd.print("Distance:");
      lcd.setCursor(9,0);
      lcd.print(Distance);

       if (strcmp(Cardinal, "N") == 0){
      //   lcd.setCursor(0,1);
      //   lcd.print("");
      //   lcd.setCursor(0,1);
      //   lcd.write((byte)1);
      //   lcd.setCursor(9,1);
         lcd.print("North");
       } else if (strcmp(Cardinal, "S") == 0){
      //   lcd.setCursor(0,1);
      //   lcd.print(""); //Clear first column in order for the next arrow
      //   lcd.setCursor(0,1);
      //   lcd.write((byte)2); //Write the arrow
      //   lcd.setCursor(9,1);
         lcd.print("South"); //Write the cardinal
       } else if (strcmp(Cardinal, "W") == 0){
      //   lcd.setCursor(0,1);
      //   lcd.print("");
      //   lcd.setCursor(0,1);
      //   lcd.write((byte)0);
      //   lcd.setCursor(9,1);
         lcd.print("West");
       } 
       else if (strcmp(Cardinal, "E") == 0){
      //   lcd.setCursor(0,1);
      //   lcd.print("");
      //   lcd.setCursor(0,1);
      //   lcd.write((byte)3);
      //   lcd.setCursor(9,1);
         lcd.print("East");
       }
       else {
      //   lcd.setCursor(0,1);
      //   lcd.print("");
      //   lcd.setCursor(0,1);
      //   lcd.setCursor(9,1);
         lcd.print(Cardinal);
       }

  }
}
}