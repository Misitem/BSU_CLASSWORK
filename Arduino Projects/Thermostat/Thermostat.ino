  #include <Servo.h> //For controlling servo
  Servo servo1;
  //Variables for temperature from thermister, temperature converted into F, and angle of servo
  int temp=0;
  int tempfar=0; 
  int angle=0;
void setup() {
  //Pins used: 3,4,5,6 > LEDs.
  // Pin 7 > Relay control
  // Pin 9 > Servo control
  
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  //digitalWrite(7, HIGH);
  Serial.begin(9600);
  servo1.attach(9);
}

void loop() {
 int input = analogRead(A0);  //Read input from sensor
 
 Serial.print("thermister");  //Printing for thermister (for scaling)
 Serial.println(input);
 
 tempfar = map(input, 480, 670, 75, 108); //Temp mapping (Scaling)
 
 angle = map(tempfar, 75, 108, 40, 150);  //Angle mapping (for analog thermometer)

 Serial.print("Farenh");  //Temp in F
 Serial.println(tempfar); //For printing temp in F
 servo1.write(angle); //Write the angle on servo
 
 delay(500);
 //digitalWrite(7,LOW);

 //If statements for turning off/on lights, and controlling relay for fan control
 if(tempfar <= 71){
    //By turning off every light above the one turned on we avoid accidental skips in lighting
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
 }

 else if(tempfar <= 75 && tempfar > 71){
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(7,LOW);
 }

 else if(tempfar < 85 && tempfar > 78){
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
 }

 else if(tempfar >= 85){
    digitalWrite(3, HIGH);
    digitalWrite(7,HIGH);
 }


}
