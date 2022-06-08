const int GREEN = 12;  //assigns green LED to pin 12
const int RED = 10;    //assigns red LED to pin 10
char data = '0';       //data variable set to 0 initially


void setup() 
{
  Serial.begin(9600);        //start serial communication
  pinMode(GREEN, OUTPUT);    //set pin mode for green LED
  pinMode(RED, OUTPUT);      //set pin mode for red LED
  digitalWrite(GREEN, LOW);  //set initial LED state as off
  digitalWrite(RED, LOW);    //set initial LED state as off
}

void loop() 
{
  if (Serial.available() > 0) //begin looking for data from transmitter
  {
    data = Serial.read(); //read data from serial communication to the data variable
    Serial.print(data);

    //uses LEDs to indicate the current GPS fix status on the local circuit at a quick glance
    //red LED on means no fix, green LED on means good fix
    
    //If fix > 0, Green LED on and Red off
    if (data > '0')
      {
        digitalWrite(GREEN, HIGH); 
        digitalWrite(RED, LOW);
      }

    //if no fix, Red LED on and Green LED off
    else if (data == '0')
      {
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, LOW);
      }
  }
}