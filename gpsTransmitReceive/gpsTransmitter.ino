//This code drew heavily on the lessons provided by Paul McWhorter from toptechboy.com

#include <Adafruit_GPS.h>      //install the adafruit GPS library
#include <SoftwareSerial.h>    //load the Software Serial library
SoftwareSerial mySerial(8,7);  //initialize the Software Serial port on Arduino pins 7 & 8
Adafruit_GPS GPS(&mySerial);   //create the GPS Object
 
String NMEA1;   //variable for first NMEA sentence
String NMEA2;   //variable for second NMEA sentence
char c;         //read characters coming from the GPS
float deg;      //will hold position data in simple degree format
float degWhole; //variable for position data
float degDec;   //variable for position data
 
 
void setup() {
  
  Serial.begin(9600);                               //begin serial communication at 9600 baud
  GPS.begin(9600);                                  //begin GPS module at 9600 baud
  GPS.sendCommand("$PGCMD,33,0*6D");                //turn off antenna update misc data
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);     //request RMC and GGA sentences
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);        //set update rate to 1 hz
  delay(1000); 
}
 
void loop() {
  
  readGPS();
 
  //print the current date
  Serial.print("Date: ");
  Serial.print(GPS.day, DEC); 
  Serial.print('/');
  Serial.print(GPS.month, DEC); 
  Serial.print("/20");
  Serial.print(GPS.year, DEC);
  Serial.print(", ");

    //print the current time
  Serial.print("Time (GMT): ");
  if (GPS.hour < 10) { 
      Serial.print('0'); 
    }
    Serial.print(GPS.hour, DEC); 
    Serial.print(':');
  if (GPS.minute < 10) { 
      Serial.print('0'); 
      }
    Serial.print(GPS.minute, DEC); 
    Serial.print(':');
  if (GPS.seconds < 10) { 
      Serial.print('0'); 
      }
    Serial.print(GPS.seconds, DEC); 
    Serial.println(" ");

  //latitude conversion from DDMM.MMMMM to decimal degrees
  degWhole=float(int(GPS.latitude/100));       //divides by 100 and converts to int to give the whole degree part of latitude
  degDec = (GPS.latitude - degWhole*100)/60;   //give fractional part of latitude
  deg = degWhole + degDec;                     //gives complete decimal form of latitude
  
  //changes latitude to negative value if in southern hemisphere
  if (GPS.lat=='S') {  
    deg= (-1)*deg;
  }
  //Print longitude data
  Serial.print(deg,4); 
  Serial.print(","); 

  //longitude conversion from DDMM.MMMMM to decimal degrees
  degWhole=float(int(GPS.longitude/100));       //divides by 100 and converts to int to give the whole degree part of latitude
  degDec = (GPS.longitude - degWhole*100)/60;   //give fractional part of longitude
  deg = degWhole + degDec;                      //gives complete decimal form of longitude
  
  //changes latitude to negative value if in western hemisphere
  if (GPS.lon=='W') {  
    deg= (-1)*deg;
  }
  //print latitude data
  Serial.print(deg,4);
  Serial.println(",");

  //other data
  Serial.print("Altitude: ");
  Serial.print(GPS.altitude);        //alititude
  Serial.print(" m, ");
  Serial.print("Angle: ");
  Serial.print(GPS.angle);           //bearing
  Serial.print("°, ");
  Serial.print("Speed: "); 
  Serial.print(GPS.speed);           //speed (in knots)
  Serial.print(" kn, ");
  Serial.print("Satellite Count: ");
  Serial.println(GPS.satellites);    //# of satellites seen by GPS
  Serial.println(" ");
}

//function for readGPS 
void readGPS() {
  
  clearGPS();
  while(!GPS.newNMEAreceived()) { //loop until you have a good NMEA sentence
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //parse the good NMEA sentence
  NMEA1=GPS.lastNMEA();
  
   while(!GPS.newNMEAreceived()) { //loop until you have a good NMEA sentence
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //parse the good NMEA sentence
  NMEA2=GPS.lastNMEA();

  //uncomment the next 3 lines to print the NMEA sentences for GGA and RMC if desired
  //Serial.println(NMEA1);
  //Serial.println(NMEA2);
  //Serial.println("");
  
}

//function to clear bad GPS data from buffer, three loops seems to work best
void clearGPS() {  
  while(!GPS.newNMEAreceived()) { //loop until you have a good NMEA sentence
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //parse the good NMEA sentence
  
  while(!GPS.newNMEAreceived()) { //loop until you have a good NMEA sentence
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //parse the good NMEA sentence
   while(!GPS.newNMEAreceived()) { //loop until you have a good NMEA sentence
    c=GPS.read();
  }
  GPS.parse(GPS.lastNMEA()); //parse the good NMEA sentence
  
}
