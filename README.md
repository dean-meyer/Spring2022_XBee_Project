### Spring 2022 Undergraduate Physics Research Project </br>
This repository is for my Spring 2022 Undergraduate Physics Research Project at [Augusta University](https://www.augusta.edu/scimath/chemistryandphysics/index.php), advised by [Dr. Andy Hauger](https://www.augusta.edu/scimath/chemistryandphysics/andyhauger.php). </br></br>
The purpose of this project was to create an [Arduino](https://www.arduino.cc) controlled [XBee](https://www.digi.com/xbee) system to enable the wireless transmission of data from remote sensors. Two example uses are included in this repository. ledTransmitReceive uses XBee radios to remotely turn on an LED using a standard button connected to an Arduino. gpsTransmitReceive uses XBee radios to transmit data from a remote Adafruit GPS module to a local XBee receiver, including conversion of the latittude and longitude from the default NMEA format DDMM.MMMM to Decimal Degrees.</br></br>
The GPS data is currently configured to display the following output:</br>
![Sample Output](https://github.com/dean-meyer/Spring2022_XBee_Project/blob/main/images/Sample%20Output.png 'Sample Output')
