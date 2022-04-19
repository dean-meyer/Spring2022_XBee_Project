const int LED = 12; //assigns Blue LED to pin 12
char data = '0'; //data variable set to 0 initially


void setup() 
{
  Serial.begin(9600); //start serial communication
  pinMode(LED, OUTPUT); 
  digitalWrite(LED, LOW); 
}

void loop() 
{
  if (Serial.available() > 0) //if statement to beging looking for data from transmitter
  {
    data = Serial.read(); //read data from serial comm to the data variable

    //button is pressed turn on the LED, if it's not turn it off
    if (data > '0')
      {
        digitalWrite(LED, HIGH); 
      }

    //if no fix, Red LED on and Blue LED off
    else if (data == '0')
      {
        digitalWrite(LED, LOW);
      }
  }
}
