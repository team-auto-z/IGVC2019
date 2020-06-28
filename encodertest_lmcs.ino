//Right Wheel 
int encoderPin1 = 20;
int encoderPin2 = 21;


volatile int lastEncodedR = 0;
volatile int encoderValueR = 0;

long lastencoderValueR = 0;

int lastMSBR = 0;
int lastLSBR = 0;



//Left Wheel
int encoderPin3 = 18;
int encoderPin4 = 19; 

volatile int lastEncodedL = 0;
volatile int encoderValueL = 0;

long lastencoderValueL = 0;

int lastMSBL = 0;
int lastLSBL = 0;



void setup() {
  Serial.begin (9600);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
  pinMode(encoderPin3, INPUT); 
  pinMode(encoderPin4, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
  
  digitalWrite(encoderPin3, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin4, HIGH); //turn pullup resistor on



  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 

  
  attachInterrupt(digitalPinToInterrupt(20), updateEncoderLeft, HIGH); 
  attachInterrupt(digitalPinToInterrupt(21), updateEncoderLeft, HIGH);
  
  attachInterrupt(digitalPinToInterrupt(18), updateEncoderRight, HIGH); 
  attachInterrupt(digitalPinToInterrupt(19), updateEncoderRight, HIGH);

}

void loop(){ 
  //Do stuff here

    detachInterrupt(digitalPinToInterrupt(20)); 
    detachInterrupt(digitalPinToInterrupt(21)); 
    detachInterrupt(digitalPinToInterrupt(18)); 
    detachInterrupt(digitalPinToInterrupt(19)); 
  
    Serial.print(encoderValueL);
    Serial.print(" "); 
    Serial.println(encoderValueR);
  
    attachInterrupt(digitalPinToInterrupt(20), updateEncoderLeft, HIGH); 
    attachInterrupt(digitalPinToInterrupt(21), updateEncoderLeft, HIGH);
    attachInterrupt(digitalPinToInterrupt(20), updateEncoderRight, HIGH); 
    attachInterrupt(digitalPinToInterrupt(21), updateEncoderRight, HIGH);
  
}

void updateEncoderRight(){
  int MSBR = digitalRead(encoderPin1); //MSB = most significant bit
  int LSBR = digitalRead(encoderPin2); //LSB = least significant bit

  int encodedR = (MSBR << 1) |LSBR; //converting the 2 pin value to single number
  int sum  = (lastEncodedR << 2) | encodedR; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValueR ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValueR --;

  lastEncodedR = encodedR; //store this value for next time
 
}


void updateEncoderLeft(){
  int MSBL = digitalRead(encoderPin3); //MSB = most significant bit
  int LSBL = digitalRead(encoderPin4); //LSB = least significant bit

  int encodedL = (MSBL << 1) |LSBL; //converting the 2 pin value to single number
  int sum  = (lastEncodedL << 2) | encodedL; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValueL ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValueL --;

  lastEncodedL = encodedL; //store this value for next time
 
}
