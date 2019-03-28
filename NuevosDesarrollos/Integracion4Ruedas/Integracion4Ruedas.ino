#include <AFMotor.h> 
#include <Servo.h> 
#include <NewPing.h>      //add Ultrasonic sensor library

//creates two objects to control the terminal 3 and 4 of motor shield
AF_DCMotor motor1(3);
AF_DCMotor motor2(4);
AF_DCMotor motor3(1);
AF_DCMotor motor4(2);
Servo myservo; 
#define TRIG_PIN A4 // Pin A0 on the Motor Drive Shield soldered to the ultrasonic sensor
#define ECHO_PIN A5 // Pin A1 on the Motor Drive Shield soldered to the ultrasonic sensor
#define MAX_DISTANCE 300 // sets maximum useable sensor measuring distance to 300cm
#define COLL_DISTMin 10 // sets distance at which robot stops and reverses to 30cm
#define COLL_DIST 30 // sets distance at which robot stops and reverses to 30cm
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
char command;
boolean isSmart=false;
int leftDistance, rightDistance;
int smartFlag=0;
int curDist = 0;
String motorSet = "";
int speedSet = 0;

 void setup() { 
     Serial.begin(9600); //Set the baud rate to your Bluetooth module. 
     myservo.attach(10);
     myservo.write(90);
     delay(90); // delay for one seconds
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
 break; 
 case 'X':
 setAutonomus();
 break;
 }
 }
 if( isSmart==true){
   myservo.write(90);  
  delay(90);
  curDist = readPing();  
    if (curDist < COLL_DIST) {changePath();}  // if forward is blocked change direction
  forward();  // move forward
  delay(500);
  }
 }
 void changePath() {
  moveStop();   // stop forward movement
  myservo.write(36);  // check distance to the right
    delay(500);
    rightDistance = readPing(); //set right distance
    delay(500);
    myservo.write(144);  // check distace to the left
    delay(700);
    leftDistance = readPing(); //set left distance
    delay(500);
    myservo.write(90); //return to center
    delay(100);
    compareDistance();
  }
  
void compareDistance()   // find the longest distance
{
   if (leftDistance>rightDistance) //if left is less obstructed 
  {
    turnLeft();
  }
  else if (rightDistance>leftDistance) //if right is less obstructed
  {
    turnRight();
  } 
}
void turnAround(){
  motor1.setSpeed(255); 
motor1.run(FORWARD); 
motor2.setSpeed(255); 
motor2.run(FORWARD); 
motor3.setSpeed(0); 
motor3.run(RELEASE); 
motor4.setSpeed(0); 
motor4.run(RELEASE);  
  delay(4000); // run motors this way for 1500       
  motor1.setSpeed(255); 
motor1.run(FORWARD); 
motor2.setSpeed(255); 
motor2.run(FORWARD); 
motor3.setSpeed(255); 
motor3.run(FORWARD); 
motor4.setSpeed(255); 
motor4.run(FORWARD);   
  }
  void turnRight() {
motor1.setSpeed(255); 
motor1.run(FORWARD); 
motor2.setSpeed(255); 
motor2.run(FORWARD); 
motor3.setSpeed(0); 
motor3.run(RELEASE); 
motor4.setSpeed(0); 
motor4.run(RELEASE);  
  delay(2000); // run motors this way for 1500       
  motor1.setSpeed(255); 
motor1.run(FORWARD); 
motor2.setSpeed(255); 
motor2.run(FORWARD); 
motor3.setSpeed(255); 
motor3.run(FORWARD); 
motor4.setSpeed(255); 
motor4.run(FORWARD);   
  }  
 void turnLeft(){
  motor1.setSpeed(0); 
motor1.run(RELEASE); 
motor2.setSpeed(0); 
motor2.run(RELEASE); 
motor3.setSpeed(255); 
motor3.run(FORWARD); 
motor4.setSpeed(255); 
motor4.run(FORWARD);  
  delay(2000); // run motors this way for 1500       
  motor1.setSpeed(255); 
motor1.run(FORWARD); 
motor2.setSpeed(255); 
motor2.run(FORWARD); 
motor3.setSpeed(255); 
motor3.run(FORWARD); 
motor4.setSpeed(255); 
motor4.run(FORWARD);   
  }
  
  void moveStop() {motor1.run(RELEASE); motor2.run(RELEASE); motor3.run(RELEASE); motor4.run(RELEASE);}  // stop the motors.

int readPing() { // read the ultrasonic sensor distance
  delay(70);   
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  Serial.print(cm);
  Serial.print("cm");
Serial.println();
  return cm;
}
 void setAutonomus(){
  smartFlag=0;
  if(isSmart==false){
    isSmart=true;
    smartFlag=1;
    }
  if(isSmart==true && smartFlag==0){
  isSmart=false;
  }
  }
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
