#include <Arduino.h>
void StartWebServer(){

}


void MotorControl(int Motor, int Speed){
  int Forward[2] = {0, 14};
  int Backward[2] = {4, 12};
  if (Speed > 0){
    analogWrite(Backward[Motor], 0);
    analogWrite(Forward[Motor], PWMRANGE * (Speed * 0.01));
  } else if (Speed < 0){
    analogWrite(Forward[Motor], 0);
    analogWrite(Backward[Motor], PWMRANGE * (Speed * -0.01));
  } else {
    analogWrite(Forward[Motor], 0);
    analogWrite(Backward[Motor], 0);
  }
}

void setup() {
  pinMode(0, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(12, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=-100; i<100; i=i+5){
    MotorControl(1, i);
    delay(1000);
  }
  for(int i=100; i>-100; i=i-5){
    MotorControl(1, i);
    delay(1000);
  }
}
