#include <AFMotor.h> 
#include <Servo.h> 
//creates two objects to control the terminal 3 and 4 of motor shield
AF_DCMotor motor1(3);
AF_DCMotor motor2(4);
AF_DCMotor motor3(1);
AF_DCMotor motor4(2);
Servo myservo; 
char command;
 void setup() { 
     Serial.begin(9600); //Set the baud rate to your Bluetooth module. 
     myservo.attach(10);
     myservo.write(90);
} 
void loop(){ 
if(Serial.available() > 0){
 command = Serial.read();
 Stop(); //initialize with motors stoped
 //Change pin mode only if new command is different from previous.
 Serial.println(command); 
switch(command){ 
case 'F':
 forward();
break;
 case 'B':
 back();
 break; 
case 'L': 
left(); 
break; 
case 'R':
 right();
 break; }
 } }
 void forward() { 
  motor1.setSpeed(255); 
motor1.run(FORWARD); 
motor2.setSpeed(255); 
motor2.run(FORWARD); 
motor3.setSpeed(255); 
motor3.run(FORWARD); 
motor4.setSpeed(255); 
motor4.run(FORWARD); 

} 
void back() { 
motor1.setSpeed(255); 
motor1.run(BACKWARD); 
motor2.setSpeed(255); 
motor2.run(BACKWARD); 
motor3.setSpeed(255); 
motor3.run(BACKWARD); 
motor4.setSpeed(255); 
motor4.run(BACKWARD); 

} 
void left() { 
motor1.setSpeed(0); 
motor1.run(RELEASE); 
motor2.setSpeed(0); 
motor2.run(RELEASE); 
motor3.setSpeed(255); 
motor3.run(FORWARD); 
motor4.setSpeed(255); 
motor4.run(FORWARD); 
} 
void right() {
motor1.setSpeed(255); 
motor1.run(FORWARD); 
motor2.setSpeed(255); 
motor2.run(FORWARD); 
motor3.setSpeed(0); 
motor3.run(RELEASE); 
motor4.setSpeed(0); 
motor4.run(RELEASE); 
 }
 void Stop() { 
 motor1.setSpeed(0); 
motor1.run(RELEASE); 
motor2.setSpeed(0); 
motor2.run(RELEASE); 
motor3.setSpeed(0); 
motor3.run(RELEASE); 
motor4.setSpeed(0); 
motor4.run(RELEASE); 
 } 
