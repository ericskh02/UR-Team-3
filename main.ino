#include <NewPing.h>

//Speed for the motor
#define defined_speed 35

//Ultrasonic Sensor Setup
#define TRIGGER_PIN_1 2
#define ECHO_PIN_1 3
#define TRIGGER_PIN_2 4
#define ECHO_PIN_2 5
#define MAX_DISTANCE 200

NewPing ultrasonic1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing ultrasonic2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);

int left_distance = 0;
int front_distance = 0;

//Motor Setup
#define motor1_in1 6
#define motor1_in2 9
#define motor2_in1 10
#define motor2_in2 11

//Time delay setup
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

//Maze
bool mazeSolved = true;

//Ultrasonic Sensor Reading
int getFrontDistance(){
  return front_distance;
}

int getLeftDistance(){
  return left_distance;  
}
//Movement of Robot
void brake(){
  analogWrite(motor1_in1,255);
  analogWrite(motor1_in2,255);
  analogWrite(motor2_in1,255);
  analogWrite(motor2_in2,255);  
}

void moveForward(int speed){
  analogWrite(motor1_in1,speed);
  analogWrite(motor1_in2,0);
  analogWrite(motor2_in1,speed);
  analogWrite(motor2_in2,0);
}

void turnLeft(int speed){
  analogWrite(motor1_in1,0);
  analogWrite(motor1_in2,speed);
  analogWrite(motor2_in1,speed);
  analogWrite(motor2_in2,0);
}

void turnRight(int speed){
  analogWrite(motor1_in1,speed);
  analogWrite(motor1_in2,0);
  analogWrite(motor2_in1,0);
  analogWrite(motor2_in2,speed);
} 

void moveBackward(int speed){
  analogWrite(motor1_in1,0);
  analogWrite(motor1_in2,speed);
  analogWrite(motor2_in1,0);
  analogWrite(motor2_in2,speed);  
}

void moveForward(unsigned long time, int speed){
  previousMillis = 0;
  while(true){
    if(Serial.available()>0){
      break;
    }
    currentMillis = millis();  
    if(currentMillis - previousMillis >= time){
      previousMillis = currentMillis;
      break;
    }
    analogWrite(motor1_in1,speed);
    analogWrite(motor1_in2,0);
    analogWrite(motor2_in1,speed);
    analogWrite(motor2_in2,0);
  }
  brake();
}

void turnLeft(unsigned long time,int speed){
  previousMillis = 0;
  while(true){
    if(Serial.available()>0){
      break;
    }
    currentMillis = millis();
    if(currentMillis - previousMillis >= time){
      previousMillis = currentMillis;
      break;
    }
    analogWrite(motor1_in1,0);
    analogWrite(motor1_in2,speed);
    analogWrite(motor2_in1,speed);
    analogWrite(motor2_in2,0);
  }
  brake();
}

void turnRight(unsigned long time, int speed){
  previousMillis = 0;
  while(true){
    if(Serial.available()>0){
      break;
    }
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= time){
      previousMillis = currentMillis;
      break;  
    }  
  analogWrite(motor1_in1,speed);
  analogWrite(motor1_in2,0);
  analogWrite(motor2_in1,0);
  analogWrite(motor2_in2,speed);
  }
  brake();
} 

void moveBackward(unsigned long time, int speed){
  unsigned long previousMillis = 0;
  while(true){
    if(Serial.available()>0){
      break;
    }
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis ){
      previousMillis = currentMillis;
      break;
    }
    analogWrite(motor1_in1,0);
    analogWrite(motor1_in2,speed);
    analogWrite(motor2_in1,0);
    analogWrite(motor2_in2,speed);
  }
  brake();
}

void startMaze(bool leftMode){
  mazeSolved = false;
}

void setMazeCompleted(){
  mazeSolved = true;
}
//Bluetooth Connection and Command Setup
byte command;
void executeCommand(int command){
  Serial.println(command);
  switch(command){
    case 5:
      brake();
      break;
    case 1:
      moveForward(defined_speed);
      break;
    case 2:
      turnLeft(defined_speed);
      break;
    case 3:
      turnRight(defined_speed);
      break;
    case 4:
      moveBackward(defined_speed);
      break;
    case 10:
      startMaze(true);
      break;
    case 11:
      setMazeCompleted();
      break;
    case 123:
      Serial.println("test hi");
      break;
    default:
      Serial.println(command);
      break;
  }
}

void setup() {
  Serial.begin(9600);
  // pinMode of ultrasonic sensors are defined in NewPing library itself
  pinMode(motor1_in1,OUTPUT);
  pinMode(motor1_in2,OUTPUT);
  pinMode(motor2_in1,OUTPUT);
  pinMode(motor2_in2,OUTPUT);
}

void loop() {
  front_distance = ultrasonic1.ping_cm();
  left_distance = ultrasonic2.ping_cm();

  if(Serial.available()){
    command = Serial.read();
    executeCommand(command);
  }

  if(!mazeSolved){ // Zero rule: if the maze is not completed
    if(left_distance>=30){ // First rule: if there is road to left
      moveForward(1000,defined_speed);
      turnLeft(2000,defined_speed);
      moveForward(1000,defined_speed);
    } else if (front_distance<=8){ // Second rule: if there is road forward
      moveForward(100,defined_speed);
      } else { //Third rule: if there is no road for left and forward
        turnRight(2000,defined_speed);
    }  
  }
}
  
