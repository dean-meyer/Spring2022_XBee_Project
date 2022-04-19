const int LED = 12;    //assigns  LED to pin 12
char data = '0';       //data variable set to 0 initially


void setup() 
{
  Serial.begin(9600);        //start serial communication
  pinMode(LED, OUTPUT);      //set pinMode for LED as output
  digitalWrite(LED, LOW);    //set initial state of LED off
}

void loop() 
{
  if (Serial.available() > 0)   //if statement to begin looking for data from transmitter
  {
    data = Serial.read();       //read data from serial comm to the data variable

    //if button is pressed turn on the LED
    if (data > '0')
      {
        digitalWrite(LED, HIGH); 
      }

    //if button is not pressed turn LED off
    else if (data == '0')
      {
        digitalWrite(LED, LOW);
      }
  }
}
