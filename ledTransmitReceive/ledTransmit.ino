const int button = 13; //assigns the button to pin 13

void setup() 
{
  pinMode(button, INPUT); //set button as input
  Serial.begin(9600); //start serial communcation
}

void loop() 
{
  int onOff = digitalRead(button); //read 1 if pressed, 0 if not
  Serial.println(onOff); //verify reads 1 if pressed or 0 if not
  delay(50); //changing this delay will change how long it takes receiver to turn on LED
}
