//#include <Servo.h>  
#define RightMotorDir  13
#define RightMotorPwmPin 11
#define LeftMotorDir 3
#define LeftMotorPwmPin 12
#define Led1 8
#define Led2 9
unsigned long time;



//Servo ESC;  
  
#define DipSwitch1 5
#define DipSwitch2 6
#define DipSwitch3 7

#define Start 10


#define s0 A2
#define s1 A4
#define s2 A5
#define s3 4
#define Sens A1
#define Trimpot A3                                 


int a = 0;
int b=0;
int Threshold = 300;
int LimitMin = -220;
int LimitMax = 220;
int Error;
int LastError = 0;
int TotalError;
int Correction;
int BaseSpeed; 
int ExtraNos; 
int NoNos;
int NosTime;

float Kp;
float Ki;
float Kd;

int RightMotorPwm = 0;
int LeftMotorPwm = 0;
int zemin=1;
void setup() {

//ESC.attach(2); 
  
pinMode(DipSwitch1, INPUT);
pinMode(DipSwitch2, INPUT);
pinMode(DipSwitch3, INPUT);
pinMode(Start, INPUT);

digitalWrite(DipSwitch1, HIGH);
digitalWrite(DipSwitch2, HIGH);
digitalWrite(DipSwitch3, HIGH);

pinMode(2, OUTPUT);
pinMode(1, OUTPUT);
pinMode(Led1, OUTPUT);
pinMode(Led2, OUTPUT);
pinMode(s0, OUTPUT);
pinMode(s1, OUTPUT);
pinMode(s2, OUTPUT);
pinMode(s3, OUTPUT);
digitalWrite(s0, LOW);
digitalWrite(s1, LOW);
digitalWrite(s2, LOW);
digitalWrite(s3, LOW);
for (int xp=0; xp < 3; xp++) {
  digitalWrite(Led1, HIGH);
  digitalWrite(Led2, HIGH);
   digitalWrite(1, HIGH);
      delay(500);
        digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
       digitalWrite(1, LOW);
      delay(500);
}
int SpeedPlus=analogRead(Trimpot);
BaseSpeed=(30+(SpeedPlus/8)); // Min 30 - Max 178
ExtraNos = BaseSpeed+10;
NoNos = BaseSpeed;

      pinMode(Sens,INPUT);
      pinMode(RightMotorDir, OUTPUT);
      pinMode(RightMotorPwmPin, OUTPUT);
      pinMode(LeftMotorDir, OUTPUT);
      pinMode(LeftMotorPwmPin, OUTPUT);
      
Serial.begin(9600);
}
int ReadSensor(){

  for (int i=0; i <= 15; i++){
    if (i == 0)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
           a=7500;
           b=500;
        }}
     else  if (i == 1)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
           a=6500;
           b=500;
        }
    }  
    else if (i == 2)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
   a=5500;
   b=500;
        }
    }
    else if (i == 3)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
      if(analogRead(Sens)<Threshold){
   a=4500;
   b=500;
        }
    }
    else if (i == 4)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
      if(analogRead(Sens)<Threshold){
      a=3500;
    }

    }
    else if (i == 5)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
   a=2500;
        }
    }
    else if (i == 6)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
    a=1500;
        }
    }
  
    else if (i == 7)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
        if(analogRead(Sens)<Threshold){
    a=500;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    }}
    else if (i == 8)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
      if(analogRead(Sens)<Threshold){
      a=-500; 
    }
 
    }
    else if (i ==9)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
        if(analogRead(Sens)<Threshold){
       a=-1500;
    }
    }
    else if (i == 10)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
      if(analogRead(Sens)<Threshold){
      a=-2500;
    }
    
    }
    else if (i == 11)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
        if(analogRead(Sens)<Threshold){
   a=-3500;
   b=-500;
        }
    }
    else if (i == 12)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
        if(analogRead(Sens)<Threshold){
        a=-4500;
        b=-500;
        }
    }
    else if (i == 13)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
        if(analogRead(Sens)<Threshold){
    a=-5500; 
    b=-500;
        }
    }
    else if (i == 14)
    {
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
        if(analogRead(Sens)<Threshold){
     a=-6500;
     b= -500;
        }
    }
    else if (i == 15)
    {
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
      if(analogRead(Sens)<Threshold){
      a=-7500;
    }}
  
  }
}

void MotorControl(int LeftMotorPwm, int RightMotorPwm){

  if(LeftMotorPwm<=0) {
       LeftMotorPwm=abs(LeftMotorPwm);
      digitalWrite(LeftMotorDir, LOW);
      analogWrite(LeftMotorPwmPin, LeftMotorPwm);
    }
  else {
      digitalWrite(LeftMotorDir, HIGH);
      analogWrite(LeftMotorPwmPin, LeftMotorPwm);
}
       
    
  if(RightMotorPwm <= 0) {
     RightMotorPwm=abs(RightMotorPwm);
      digitalWrite(RightMotorDir, LOW);
      analogWrite(RightMotorPwmPin, RightMotorPwm);
    }
  else {
      digitalWrite(RightMotorDir, HIGH);
      analogWrite(RightMotorPwmPin, RightMotorPwm);
      }
  } 



//************************************
void MotorControl2(int LeftMotorPwm, int RightMotorPwm){

  if(LeftMotorPwm<=(BaseSpeed-10)) {
      LeftMotorPwm=(BaseSpeed-LeftMotorPwm)*2;
      digitalWrite(LeftMotorDir, LOW);
      analogWrite(LeftMotorPwmPin, LeftMotorPwm);
    }
  else if (LeftMotorPwm>(BaseSpeed+10)){
    LeftMotorPwm=(LeftMotorPwm-BaseSpeed)*2;
      digitalWrite(LeftMotorDir, HIGH);
      analogWrite(LeftMotorPwmPin, LeftMotorPwm);
}
    else {analogWrite(LeftMotorPwmPin, 0);}
    
  if(RightMotorPwm<=(BaseSpeed-10)) {
      RightMotorPwm=(BaseSpeed-RightMotorPwm)*2;
      digitalWrite(RightMotorDir, LOW);
      analogWrite(RightMotorPwmPin, RightMotorPwm);
    }
  else if (RightMotorPwm>(BaseSpeed+10)){
    RightMotorPwm=(RightMotorPwm-BaseSpeed)*2;
      digitalWrite(RightMotorDir, HIGH);
      analogWrite(RightMotorPwmPin, RightMotorPwm);
      }
      else {analogWrite(RightMotorPwmPin, 0);}
  } 



void loop() {
    Serial.print("BaseSpeed = ");
    Serial.print(BaseSpeed);
    delay(100);
       while (1){
/*time = micros();
time = time % 16500;
if (time < 1200){
digitalWrite(2, HIGH);
} else 
{digitalWrite(2, LOW);
} 

//Serial.println(time);

       
    */   
 
//  while(digitalRead(Start)==0) {MotorControl(0,0); digitalWrite(Led1, HIGH); digitalWrite(Led2, HIGH);} 
    digitalWrite(Led1, LOW); digitalWrite(Led2, LOW);

  BaseSpeed = NoNos;
  ReadSensor();

  if (b=0) {a=b;}

    Error = a;
    if (Error == 0 ) {TotalError=0;}
    TotalError = TotalError+Error;
    if (TotalError >= 15000 ) {TotalError=15000;}
    if (TotalError <= -15000 ) {TotalError=-15000;}
    
    Correction = Kp * Error + Ki*TotalError + Kd*(Error - LastError);
    LastError = Error;
 
    RightMotorPwm = BaseSpeed + Correction  ;
    LeftMotorPwm = BaseSpeed - Correction  ;
    
    RightMotorPwm = constrain(RightMotorPwm, LimitMin, LimitMax); 
    LeftMotorPwm = constrain(LeftMotorPwm, LimitMin, LimitMax); 
    MotorControl(LeftMotorPwm, RightMotorPwm);
    //MotorControl2(LeftMotorPwm, RightMotorPwm);

    //Kp 0,55 Kd 60 
    if (digitalRead(DipSwitch1)==1) {Kp=0.55;} else {Kp=0.8;}
    if (digitalRead(DipSwitch2)==1) {int LimitMin = -180; int LimitMax = 180;} else {int LimitMin = -250; int LimitMax = 250;}
    if (digitalRead(DipSwitch3)==1) {Kd=30.00;} else {Kd=60.00;}


  /*
    Serial.print("Kp-LMin-Kd ");
    Serial.print(Kp);
    Serial.print("  ") ;
    Serial.print(LimitMin);
    Serial.print("  ") ;
    Serial.print(Kd);
    Serial.print("  ") ;*/
/*
    Serial.print("BSpeed = ");
    Serial.print(BaseSpeed);
    Serial.print('\t') ; 

    Serial.print("a= ");
    Serial.print(Error);
    Serial.print('\t') ;
    Serial.print("b= ");
    Serial.print(b);
    Serial.print('\t') ;  
    Serial.print("TotalError = ");
    Serial.print(TotalError);
    Serial.print('\t') ;
    Serial.print("Correction = ");
    Serial.print(Correction);
    Serial.print('\t') ; 
    Serial.print("LeftSpeed = ");
    Serial.print(LeftMotorPwm);
    Serial.print('\t') ; 
    Serial.print("RightSpeed = ");
    Serial.println(RightMotorPwm);
    delay(10);
     */
   Serial.print("a= ");
    Serial.println(Error);
 
  }      
}
