/*
Encoder:

interrupt pins mega: 2, 3, 18, 19, 20, 21

*/
int L1, L2, i; 
float s=0; 
const int pin1 = 2;
const int pin2 = 3;
const int pin3 = 18; 
const int pin4 = 19;  
int PR1 = 18, cnt=0; 
int PR2 = 19; 
int back; 
int state; 

int left_dir[50], l=50; 
unsigned int rpml, rpmr; // rpm reading
unsigned long pulses_left, pulses_right; // number of pulses
String dir; 
//unsigned long timeold;
// number of pulses per revolution
// based on your encoder disc
unsigned int pulsesperturn = 12;
float temp; 
c

void setup(){
  // put your setup code here, to run once:
  pinMode(pin1, INPUT);   
  pinMode(pin2, INPUT); 
//  pinMode(PR1, INPUT); 
//  pinMode(PR2, INPUT); 

  Serial.begin(9600); 
     // Initialize
   pulses_right = 0;
   pulses_left = 0;
   rpml = 0;
   rpmr = 0;
//

//   attachInterrupt(digitalPinToInterrupt(pin3), counter_right, FALLING);
   digitalWrite(pin1, HIGH);
   digitalWrite(pin2, HIGH);
   state = 2;  
   dir = "fwd"; 
}

void loop(){
//  L1 = digitalRead(pin1);
//  L2 = digitalRead(pin2); 
//  Serial.println(String(L1)+", "+String(L2));
  //dir = "stn"; 
  if(digitalRead(pin1) && digitalRead(pin2))//11
  
  {  
    if(state==1)
    dir = "bwd"; 
    else if (state==3)
    dir = "fwd";
    state=2;     
    //Serial.println("Case1"); 
//    while(digitalRead(pin2))
//    attachInterrupt(digitalPinToInterrupt(pin1), state_11_01, FALLING); //bwd
//    while(digitalRead(pin1))
//    attachInterrupt(digitalPinToInterrupt(pin2), state_11_10, FALLING);//fwd
//    //Serial.print("State1"); 
  }
  else if(!digitalRead(pin1) && digitalRead(pin2)){ //01

      if(state==0)
      dir = "fwd";
      else if(state==2)
      dir = "bwd";
      
   // Serial.println("Case2");
      state = 1;   
//    while(!digitalRead(pin2))
//    attachInterrupt(digitalPinToInterrupt(pin1), state_10_00, FALLING); //fwd
//    while(digitalRead(pin1))
//    attachInterrupt(digitalPinToInterrupt(pin2), state_10_11, RISING); //bwd
  }
  else if(digitalRead(pin1) && !digitalRead(pin2)){ //10 
      if(state==2)
      dir = "fwd";
      else if(state==0)
      dir = "bwd"; 
      state = 3;
      
   // Serial.println("Case3");
//    while(!digitalRead(pin1))
//    attachInterrupt(digitalPinToInterrupt(pin2), state_01_00, FALLING); //bwd
//    while(digitalRead(pin2))
//    attachInterrupt(digitalPinToInterrupt(pin1), state_01_11, RISING); //fwd
  } 
  else if(!digitalRead(pin1) && !digitalRead(pin2)){ //00
      if(state==3)
      dir = "fwd";
      else if(state==1)
      dir = "bwd"; 
      state = 0;      
      
   // Serial.println("Case4");
//    while(!digitalRead(pin1))
//    attachInterrupt(digitalPinToInterrupt(pin2), state_00_01, RISING); //fwd
//    while(!digitalRead(pin2))
//    attachInterrupt(digitalPinToInterrupt(pin1), state_00_10, RISING); //bwd
  }
//  detachInterrupt(digitalPinToInterrupt(pin1)); 
//  detachInterrupt(digitalPinToInterrupt(pin2)); 
//  delay(200);  
      //if(millis()%10==0)
//      delay(1); 
     
     // Serial.println(dir); 
     
//AVERAGING OVER 20 time instances      
      if(l>=0)
     left_dir[--l]=dir=="fwd"?1:0;
      else {
      l=50; 
      for (i=0;i<l; i++)
       s+=left_dir[i]; 
     //dir
     cnt = ((s/50)>=0.5)?cnt+1:cnt-1; 
 Serial.print(((s/50)>=0.5)?"fwd ":"rvs ");
 //ticks
 Serial.println(cnt); 
 s=0; 
 }
// Serial.println(pulses_left/13); 
 

}
