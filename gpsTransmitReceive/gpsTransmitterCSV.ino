/*This code largely the same as the code found in gpsTransmitter.ino, but transmits 
the data in a csv-friendly format for further use such as creating a KML. The only 
output is latitude, longitude, and altitude.
*/

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

  //longitude conversion from DDMM.MMMMM to decimal degrees
  degWhole=float(int(GPS.longitude/100));       //divides by 100 and converts to int to give the whole degree part of latitude
  degDec = (GPS.longitude - degWhole*100)/60;   //give fractional part of longitude
  deg = degWhole + degDec;                      //gives complete decimal form of longitude
  
  //changes longitude to negative value if in western hemisphere
  if (GPS.lon=='W') {  
    deg= (-1)*deg;
  }
  //print longitude data
  Serial.print(deg,4);
  Serial.print(",");

 //latitude conversion from DDMM.MMMMM to decimal degrees
  degWhole=float(int(GPS.latitude/100));       //divides by 100 and converts to int to give the whole degree part of latitude
  degDec = (GPS.latitude - degWhole*100)/60;   //give fractional part of latitude
  deg = degWhole + degDec;                     //gives complete decimal form of latitude
  
  //changes latitude to negative value if in southern hemisphere
  if (GPS.lat=='S') {  
    deg= (-1)*deg;
  }
  //Print latitude data
  Serial.print(deg,4); 
  Serial.print(","); 

  Serial.print(GPS.altitude);        //alititude
  Serial.print(",");
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
