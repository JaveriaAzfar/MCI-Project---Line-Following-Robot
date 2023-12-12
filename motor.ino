#include <Servo.h>
Servo servo1;
int servo_control;
int servo_pin = 10;
bool automatic=false;
char command;

int ena = 5; //pwm of motors
int enb = 11;
int in1 = 7; //forward for left motor
int in2 = 6; //
int in3 = 8;
int in4 = 9;
int left_motor_speed = 80;  
int right_motor_speed = 90;
int manual_speed_right = 110;
int manual_speed_left = 100;
int right_inner = A4;
int left_inner = A2;
int right_sensor = A5; //out 5 - right sensor
int left_sensor = A1; //out 1
int middle_sensor = A3;
bool object_done = false;

const int triggerPin = 12; // Ultrasonic sensor trigger pin
const int echoPin = 13;    // Ultrasonic sensor echo pin
long duration;
int distance;

void setup() {
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  servo1.attach(10);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(right_sensor, INPUT);
  pinMode(left_sensor,INPUT);
//  pinMode(sensor3,INPUT);
//  pinMode(sensor4,INPUT);
  pinMode(middle_sensor,INPUT);
  
//  close_hatch();
//  command ='s';
servo1.write(0);
  

  //configuration for BT Module
  Serial.begin(9600);
  
}

void loop() {
  // Measure distance using the ultrasonic sensor
  if (Serial.available()>0){
    command = Serial.read();
    Serial.println(command);

  }

  if (command=='R'){
    right_turn();
    Serial.println("Turning Right");
    
  }

  if (command=='F'){
    forward();
    Serial.println("Turning Left");
  }

  if (command=='L'){
    left_turn();
    Serial.println("Turning Left");
  }

  if (command=='B'){
    reverse();
    Serial.println("Reversing");
  }

  if (command=='I'){
    forward_right();
    Serial.println("Forward Right");
  }

//  if (command=='G'){
//    forward_left();
//    Serial.println("Forward Right");
//  }
//
//   if (command=='H'){
//    back_right();
//    Serial.println("Forward Right");
//  }
//
//  if (command=='J'){
//    back_left();
//    Serial.println("Forward Right");
//  }

  

if (command == 'W' or command=='w') {
    if (automatic) {
        // Turn off automatic mode
        automatic = false;
        Serial.println("Automatic Mode Off");
        halt();
    } 
    else {
        // Turn on automatic mode
        automatic = true;
        Serial.println("Automatic Mode On");
        halt();
        
    }
}


if (command == 'V' or command=='v') {
//    if (servo_state) {
//        servo_state=false;
//        //close_hatch();
//        Serial.println("Hatch closed");
//        
//    } else /{
//        // Turn on automatic mode
//        servo_state = true;
//        Serial.println("Hatch open");
//        open_hatch();   
//    }

    servo1.write(90);
}


  if (automatic==true){
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.println(distance);
    
    int LEFT_SENSOR1  = digitalRead(left_sensor);
    int RIGHT_SENSOR1 = digitalRead(right_sensor);
    
    int LEFT_SENSOR2  = digitalRead(left_inner);
    int RIGHT_SENSOR2 = digitalRead(right_inner);
    int MIDDLE_SENSOR = digitalRead(middle_sensor);

  
  if (distance > 8) { //LINE FOLLOWING CODE
      // If no obstacle is detected within 8cm, follow the line
    if(RIGHT_SENSOR1==1 && LEFT_SENSOR1==1) {
      linear(); //STOP
      Serial.println("Sensor stop");
    }

    else if((RIGHT_SENSOR1==0  && LEFT_SENSOR1==1)) {
      line_right(); //Move Right
      Serial.println("Sensor right");
    }

    else if((RIGHT_SENSOR1==1  && LEFT_SENSOR1==0)) {
      line_left(); //Move Left
      Serial.println("Sensor left");
    }

    else if(RIGHT_SENSOR2==0  && LEFT_SENSOR2==1) {
      line_right(); //Move Right
      Serial.println("Sensor right");
    }

    else if(RIGHT_SENSOR2==1  && LEFT_SENSOR2==0) {
      line_left(); //Move Left
      Serial.println("Sensor left");
    }

    else if(RIGHT_SENSOR2==0  && LEFT_SENSOR2==0) {
      linear(); //FORWARD
      Serial.println("Sensor straight");
    }

    else if(RIGHT_SENSOR1==0  && LEFT_SENSOR1==0 && RIGHT_SENSOR2==0  && LEFT_SENSOR2==0 && MIDDLE_SENSOR==0) {  
    //when a black line is detected by all sensors
      Serial.println("Perpendicular Line detected")
    }
  
  }


   else { //if (distance < 8 && distance > 6) {//OBSTACLE DETECTION
   if (object_done == false){
    object_done = true;
    Serial.println("Object Detected");
    halt(); //if the object comes within ultrasonic range
    delay(100);
    reverse();
    delay(150);
    halt();
    delay(100);
    right_turn();
    delay(200);
    halt();
    delay(100); 
    linear();
    delay(600);
    halt();
    delay(100);
    left_turn();
    delay(200);
    halt();
    delay(50);
    if(RIGHT_SENSOR1==1 && LEFT_SENSOR1==1) {
        linear(); //STOP
        Serial.println("Sensor stop");
    }

    else if((RIGHT_SENSOR1==0  && LEFT_SENSOR1==1)) {
      line_right(); //Move Right
      Serial.println("Sensor right");
    }

    else if((RIGHT_SENSOR1==1  && LEFT_SENSOR1==0)) {
      line_left(); //Move Left
      Serial.println("Sensor left");
    }

    else if(RIGHT_SENSOR2==0  && LEFT_SENSOR2==1) {
      line_right(); //Move Right
      Serial.println("Sensor right");
    }

    else if(RIGHT_SENSOR2==1  && LEFT_SENSOR2==0) {
      line_left(); //Move Left
      Serial.println("Sensor left");
    }

    else if(RIGHT_SENSOR2==0  && LEFT_SENSOR2==0) {
          linear(); //FORWARD
          Serial.println("Sensor straight");
    }
   
//---------------------------------------------------------------------------/


//--------------------------------------------------------------------------------------------------------------------------------
   
 }
    else if (object_done == true || (LEFT_SENSOR1==1 && LEFT_SENSOR2==1 && RIGHT_SENSOR1==1 &&RIGHT_SENSOR2==1 && MIDDLE_SENSOR==1 )){
    Serial.println("Obstacle Detected!!!");
    Serial.println("No. of Obstacles:", x);
    halt();  //STOp
    servo1.write(90);
    Serial.println("Servo Open");
    delay(700);
    servo1.write(0);
    Serial.println("Servo Closed");
    delay(3000);
   }
  
  }
}
 //brace for automatic condition
  else {
    halt();
  }
}

void linear(){
  analogWrite(ena, right_motor_speed);
  analogWrite(enb, left_motor_speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); //left motor
  digitalWrite(in4, LOW);
}

void halt(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); //left motor
  digitalWrite(in4, LOW);
}



void left_motor_run(){
  analogWrite(ena, right_motor_speed);
  analogWrite(enb, left_motor_speed);
  digitalWrite(in3, HIGH); //left motor
  digitalWrite(in4, LOW);
}

void right_motor_run(){
  analogWrite(ena, right_motor_speed);
  analogWrite(enb, left_motor_speed);
  digitalWrite(in1, HIGH); //right motor
  digitalWrite(in2, LOW);
}



void left_turn(){
  analogWrite(ena, right_motor_speed);
  analogWrite(enb, left_motor_speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); //left motor
  digitalWrite(in4, LOW);
}

void right_turn(){
  analogWrite(ena, right_motor_speed);
  analogWrite(enb, left_motor_speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); //left motor
  digitalWrite(in4, HIGH);
}

void reverse(){
  analogWrite(ena, manual_speed_right);
  analogWrite(enb, manual_speed_left);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); //left motor
  digitalWrite(in4, HIGH);
}


void line_right(){
  
  analogWrite(enb, 40);
  analogWrite(ena, 110);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); //left motor
  digitalWrite(in4, LOW);

}

void line_left(){
  
  analogWrite(enb, 110);
  analogWrite(ena, 40);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); //left motor
  digitalWrite(in4, LOW);

}

void forward(){
 
  analogWrite(ena, manual_speed_right);
  analogWrite(enb, manual_speed_left);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); //left motor
  digitalWrite(in4, LOW);

}

void forward_right(){
  analogWrite(ena, manual_speed_right-160);
  analogWrite(enb, manual_speed_left);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); //left motor
  digitalWrite(in4, LOW);
}

void forward_left(){
  analogWrite(ena, manual_speed_right);
  analogWrite(enb, manual_speed_left-160);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); //left motor
  digitalWrite(in4, LOW);
}

void back_right(){
  analogWrite(ena, manual_speed_right);
  analogWrite(enb, manual_speed_left-160);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); //left motor
  digitalWrite(in4, HIGH);
}

void back_left(){
  analogWrite(ena, manual_speed_right-160);
  analogWrite(enb, manual_speed_left);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); //left motor
  digitalWrite(in4, HIGH);
}
