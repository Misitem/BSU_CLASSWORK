int bit;
volatile int freq = 470;
volatile int bitsLeft=0;
volatile char currentchar=' ';  
//Serial.begin(9600); 
int speaker = 10;

void zero()
{
  freq = 420;  
}

void one()
{
  freq = 470;
}

void setup() {
pinMode(speaker,OUTPUT);


  Serial.begin(9600); 

  cli();

  TCCR1A=0;
  TCCR1B=0;

  TCNT1 = 0;

  TCCR1B |= 0b101;
  OCR1A = 16000;

  TCCR1B |= 0b1000;
  TIMSK1 |= 0b10;

  sei();
}

void loop() 
{
  if(Serial.available() > 0)
  {
   
    Serial.print("Converting the letter: -> ");
    Serial.print(char(currentchar=Serial.read()));
    Serial.println(" <- to Beeps please stand by.");
   
    bitsLeft = 10;
    //tone(speaker,150,1000);
    while(bitsLeft > 0){
      digitalWrite(speaker,HIGH);
      delayMicroseconds(1000000/freq/2);
      digitalWrite(speaker,LOW);
      delayMicroseconds(1000000/freq/2);
    }    
  }
}

ISR(TIMER1_COMPA_vect){
  Serial.println(bitsLeft);
  if(bitsLeft == 0){
    return;
  }
  if(bitsLeft == 10){
    zero();
    bitsLeft--;
  }
  else if(2 <= bitsLeft && bitsLeft <= 9){
    bit = currentchar & 1;
    if(bit==1)
    {
      one();
    }
    if(bit==0)
    {
      zero();
    }
    currentchar= currentchar >> 1;
    bitsLeft--;
  }
  else if(bitsLeft==1){
    one();
    bitsLeft--;
  }
}
