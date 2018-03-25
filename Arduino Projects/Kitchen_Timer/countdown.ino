 int datapin=4, latchpin=5, clockpin=6;
 int code = 0b11100000;

 int datapin2=7, latchpin2=8, clockpin2=9;
 int code2 = 0b11100000;

 int leftDigit;
 int rightDigit;

 volatile int count = 0;
 volatile int countEnabled=0;

 int numArray[] = { 0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110 };
 
  
 ISR (TIMER1_COMPA_vect)
 {
  if(countEnabled==0){
    return;
  }
  
  if(count!=0){
    count--;
    displayNumber(count);
  }
  else if(count==0){ 
    pinMode(10, OUTPUT);
    for(int i=0; i < 1000; i++){
      
      digitalWrite(10, HIGH);
      delay(1);
      digitalWrite(10,LOW);
      delay(1);
      countEnabled=0;
    }
    
    
  }
 }

 //int inNum = 37;
void resetCounter(){
  count=60;
  countEnabled=1;
  displayNumber(count);
}
 
void displayNumber(int inputNum) {
    leftDigit = inputNum / 10;
    rightDigit = inputNum % 10;

    digitalWrite(latchpin, LOW); 
    shiftOut(datapin, clockpin, LSBFIRST, numArray[rightDigit]);
    digitalWrite(latchpin, HIGH);
   
    digitalWrite(latchpin2, LOW);
    shiftOut(datapin2, clockpin2, LSBFIRST, numArray[leftDigit]);
    digitalWrite(latchpin2, HIGH);   //show the result
 }
 
void setup() {
  Serial.begin(9600);
  pinMode(datapin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  
  pinMode(datapin2, OUTPUT);
  pinMode(latchpin2, OUTPUT);
  pinMode(clockpin2, OUTPUT);

  displayNumber(00);
  
  attachInterrupt(0, resetCounter, FALLING);

  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  TCCR1A = 0b00000000;
  TCCR1B = 0b00001100;
  OCR1A = 62500;

  TIMSK1 = (1 << OCIE1A);

  sei();

//  digitalWrite(latchpin, LOW); 
//  shiftOut(datapin, clockpin, LSBFIRST, numArray[rightDigit]);
//  digitalWrite(latchpin, HIGH);
// 
//  digitalWrite(latchpin2, LOW);
//  shiftOut(datapin2, clockpin2, LSBFIRST, numArray[leftDigit]);
//  digitalWrite(latchpin2, HIGH);   //show the result
 
}

void loop() {
   int reading = analogRead(0);
   Serial.println(reading);
   
   if(reading >= 500){
    resetCounter();
   }
   delay(50);


}
