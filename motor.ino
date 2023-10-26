#include <Servo.h>
//Servo Configuration
Servo servo;
int servo_control;
int servo_pin=10;

//L298N Pin Configuration
int ena = 5;   //connect EnA of motor driver to pin 6 of the Arduino. 
int enb = 11;
int in1 = 7; //left
int in2 = 6; //left
int in3 = 8; //right
int in4 = 9; //right

//int in1 = 8; //left
//int in2 = 9; //left
//int in3 = 7; //right
//int in4 = 6; //right 

int left_motor_speed = 100;
int right_motor_speed =90;

void setup() {
  // put your setup code here, to run once:
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  servo.attach(10);
  close_hatch();
}

void loop() {
  // put your main code here, to run repeatedly:
//  close_hatch();
  linear();
  delay(3000);
  halt();
  delay(2000);
  
////  open_hatch();
////  delay(1000);
////  close_hatch();
////  delay(1000);

  servo.write(180);
  delay(1000);
  servo.write(90);
  delay(1000);

  rotation_360();
  delay(3000);
  halt();
  delay(1000);
  
//  left_motor_run;
  

}

void linear(){
  analogWrite(ena,left_motor_speed);
  analogWrite(enb,right_motor_speed);
  digitalWrite(in1,HIGH); //left motor
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH); //right motor
  digitalWrite(in4,LOW);
}

void halt(){

  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW); 
  digitalWrite(in4,LOW);
}

void rotation_360(){
  analogWrite(ena,right_motor_speed);
  analogWrite(enb,left_motor_speed);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW); 
  digitalWrite(in4,HIGH);
}

void open_hatch(){
  for (int i=0; i<=60;i++){
    servo.write(i);
    delay(15);
  }
  
}

void close_hatch(){
  for (int i=60; i>=0;i--){
    servo.write(i);
    delay(15);
  }
  
}

void left_motor_run(){
  analogWrite(ena,right_motor_speed);
  analogWrite(enb,left_motor_speed);
  digitalWrite(in3,HIGH); //left motor
  digitalWrite(in4, LOW);
}

void right_motor_run(){
  analogWrite(ena,right_motor_speed);
  analogWrite(enb,left_motor_speed);
  digitalWrite(in1,HIGH); //right motor
  digitalWrite(in2, LOW);
}