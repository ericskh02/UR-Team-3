#include <NewPing.h>

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
int left_defined_distance = 25;
int front_defined_distance = 10;

//Motor Setup
#define motor1_in1 6
#define motor1_in2 9
#define motor2_in1 10
#define motor2_in2 11

int defined_speed = 0; // For bluetooth control
int forward_defined_speed = 35;
int left_defined_speed = 35;
int right_defined_speed = 35;
int backward_defined_speed = 35;

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
    case 300:
      brake();
      break;
    case 301:
      moveForward(defined_speed);
      break;
    case 302:
      turnLeft(defined_speed);
      break;
    case 303:
      turnRight(defined_speed);
      break;
    case 304:
      moveBackward(defined_speed);
      break;
    case 400:
      startMaze(true);
      break;
    case 401:
      setMazeCompleted();
      break;
    case 260:
      Serial.println("test hi");
      break;
    default: // when speed is sent
      Serial.println(command); 
      defined_speed = command;
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
    if(left_distance>=left_defined_distance){ // First rule: if there is road to left
      moveForward(1000,forward_defined_speed);
      turnLeft(2000,left_defined_speed);
      moveForward(1000,forward_defined_speed);
    } else if (front_distance<=front_defined_distance){ // Second rule: if there is road forward
      moveForward(100,forward_defined_speed);
      } else { //Third rule: if there is no road for left and forward
        turnRight(2000,right_defined_speed);
    }  
  }
}
