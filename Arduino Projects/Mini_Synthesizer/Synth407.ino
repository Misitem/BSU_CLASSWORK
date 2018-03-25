#define SPEAKER 10
#define A 440
#define B 494
#define C 261
#define D 294
#define E 330
#define F 349
#define G 392

int notes[] = {E,E,F,E,D,C,E}; //"Raindrops keep falling"
int numnotes = 7;

void setup() {
 /* Serial.begin(9600);
  for(int i=0; i<numnotes; i++){
    
  
  //nonblocking command
  tone(SPEAKER,notes[i]);
  delay(280);
  noTone(SPEAKER);

  }
  */
  pinMode(SPEAKER,OUTPUT);
  while(1)
  {
  //digitalWrite(SPEAKER,HIGH);
  /*  int oldportb = PINB;
    // put a 1 in the right place
    oldportb = oldportb & 0b11111011;
    oldportb = oldportb | 0b100;
    PORTB = oldportB;*/

    PORTB = PINB | 0b00000100;

    //time for a cycle in 1/f, or 100 ms/ freq
    //we want to go high for half, low for half
    //  delay(1000/ A / 2);
  
    long t = micros(); // capture the current time
    int timeToWait;1000000 / A / 2;
    
    while(micros()-t < timeToWait)
    {
    }
    
    //digitalWrite(SPEAKER,LOW);
    PORTB = PINB & 0b11111011;
    t = micros();
    //delay(1000 / A / 2);
    
    while(micros()-t < timeToWait)
    {
    }
    
  }
}

void loop() {
  

}
