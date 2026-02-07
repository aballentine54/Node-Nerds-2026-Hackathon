#include <TinyGPSPlus.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
  const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //RS, E, D4, D5, D6, D7


// Define RX and TX pins for SoftwareSerial
#define RXPin 8
#define TXPin 9
#define GPSBaud 9600

SoftwareSerial gpsSerial(RXPin, TXPin);
TinyGPSPlus gps;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);// For the serial monitor
  lcd.begin(16,2);
  gpsSerial.begin(GPSBaud);  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  while (gpsSerial.available() > 0){
    if (gps.encode(gpsSerial.read())) {
      // 1. Check if GPS has a fix on a satellite
      if (!gps.location.isValid()) { 
          lcd.setCursor(0,0);
          lcd.print("");
        lcd.setCursor(0,0); 
        lcd.print("Waiting for GPS"); 
      return;
      }

      // Storing our current position
      double current_lat = gps.location.lat();
      double current_long = gps.location.lng();

      // Finding the distance between our current location and destination.
      double Distance = getDistance(current_lat, current_long);
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
        lcd.setCursor(0,1);
        lcd.print("                         ");
        lcd.setCursor(9,1);
        lcd.print("North");
      } else if (strcmp(Cardinal, "S") == 0){
        lcd.setCursor(0,1);
        lcd.print("                        "); //Clear first column
        lcd.setCursor(9,1);
        lcd.print("South"); //Write the cardinal
      } else if (strcmp(Cardinal, "W") == 0){
        lcd.setCursor(0,1);
        lcd.print("                            ");
        lcd.setCursor(9,1);
        lcd.print("West");
      } 
      else if (strcmp(Cardinal, "E") == 0){
        lcd.setCursor(0,1);
        lcd.print("                            ");
        lcd.setCursor(9,1);
        lcd.print("East");
      }
      else if (strcmp(Cardinal, "NE") == 0){
        lcd.setCursor(0,1);
        lcd.print("                            ");
        lcd.setCursor(1,1);
        lcd.setCursor(9,1);
        lcd.print("N.East");
      }
      else if (strcmp(Cardinal, "NW") == 0){
        lcd.setCursor(0,1);
        lcd.print("                            ");
        lcd.setCursor(1,1);
        lcd.setCursor(9,1);
        lcd.print("N.West");
      }
      else if (strcmp(Cardinal, "SE") == 0){
        lcd.setCursor(0,1);
        lcd.print("                            ");
        lcd.setCursor(1,1);
        lcd.setCursor(9,1);
        lcd.print("S.East");
      }
      else if (strcmp(Cardinal, "SW") == 0){
        lcd.setCursor(0,1);
        lcd.print("                            ");
        lcd.setCursor(1,1);
        lcd.setCursor(9,1);
        lcd.print("S.West");
      }
      
    
      else {
        lcd.setCursor(0,1);
        lcd.print("                            ");
        lcd.setCursor(0,1);
        lcd.setCursor(9,1);
        lcd.print(Cardinal);
      }
  }

}

}

  /** 
  * @param curLat current latitude of compass
    @param curLong current longitude of compass
    @return distance (in meters) from selected destination
  */
  double getDistance(double curLat, double curLong){
    // read input from potentiometer
    short selectorVal = analogRead(A0);
    double dist = 0;
    
    if(selectorVal <= 223){ 
      dist = TinyGPSPlus::distanceBetween(
        curLat, curLong,
        39.78290, -84.06158
      );
      return dist;
    }
    else if(selectorVal <= 423){ 
      dist = TinyGPSPlus::distanceBetween(
        curLat, curLong,
      39.78456, -84.0574);
      return dist;
    }
    else if(selectorVal <= 623){ 
      dist = TinyGPSPlus::distanceBetween(
        curLat, curLong,
      39.779767, -84.055217);
      return dist;
    }
    else if(selectorVal <= 823){ 
      dist = TinyGPSPlus::distanceBetween(
        curLat, curLong,
      39.787017, -84.055217);
      return dist;
    }
    else if(selectorVal > 942 && selectorVal <= 964){ // so hidden spot isn't found as easily
      dist = TinyGPSPlus::distanceBetween(
          curLat, curLong, 
          39.77707, -84.06941); // easter egg spot {:
          return dist; 
    }
    else { 
      dist = TinyGPSPlus::distanceBetween(
        curLat, curLong,
      39.781983, -84.052233);
      return dist;
    }



}