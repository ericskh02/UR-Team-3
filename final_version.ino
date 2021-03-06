#include <NewPing.h>
#include "SR04.h"
bool leftMode = true;

//Motor Setup
#define left_in1 10
#define left_in2 11
#define right_in1 6
#define right_in2 9

int defined_speed = 100; // For bluetooth control
int turn_defined_speed = 50;
//For auto maze
int forward_defined_speed = 50;
int left_defined_speed = 50;
int right_defined_speed = 50;
int backward_defined_speed = 50;

int forward_defined_time = 200;
int left_defined_time = 200;
int right_defined_time = 200;
int backward_defined_time = 200;

int justin_defined_speed = 100;

//UltraSonicDistanceSensor distanceSensor(13, 12);

#define TRIGGER_PIN_Front 2
#define ECHO_PIN_Front 3
#define TRIGGER_PIN_Right 4
#define ECHO_PIN_Right 5
#define TRIGGER_PIN_Left 12
#define ECHO_PIN_Left A1

int back = 0;

int justin_left_defined_distance = 30;
int justin_front_defined_distance = 18;
int justin_right_defined_distance = 30;

int justin_tooclose_defined_distance = 1;

SR04 sr04_left = SR04(ECHO_PIN_Left,TRIGGER_PIN_Left);
SR04 sr04_front = SR04(ECHO_PIN_Front,TRIGGER_PIN_Front);
SR04 sr04_right = SR04(ECHO_PIN_Right,TRIGGER_PIN_Right);

double duration_1;
int left_distance = 0;
int front_distance = 0;
int right_distance = 0;
int front_defined_distance = 30;
int left_defined_distance = 40;
int right_defined_distance = 40;
int tooclose_defined_distance = 5;

bool front_has_wall = false;
bool left_has_wall = true;
bool right_has_wall = true;
bool left_tooclose = false;
bool right_tooclose = true;
bool front_tooclose = false;

//Time delay setup
unsigned long previousMillis = 0;

//Maze
bool mazeSolved = true;
bool firstTurn = true;
bool justin_mazeSolved = true;

//Movement of Robot
void brake(){
  analogWrite(right_in1,255);
  analogWrite(right_in2,255);
  analogWrite(left_in1,255);
  analogWrite(left_in2,255);  
}

// the connection of the motors is not well set uo and may need further re-soldering
void moveForward(int speed){
  analogWrite(left_in1,speed);
  analogWrite(left_in2,0);
  analogWrite(right_in1,speed);
  analogWrite(right_in2,0);
}

void turnLeft(int speed){
  analogWrite(left_in1,0);
  analogWrite(left_in2,speed);
  analogWrite(right_in1,speed);
  analogWrite(right_in2,0);

}

void turnRight(int speed){
  analogWrite(left_in1,speed);
  analogWrite(left_in2,0);
  analogWrite(right_in1,0);
  analogWrite(right_in2,speed);
} 

void moveBackward(int speed){
  analogWrite(left_in1,0);
  analogWrite(left_in2,speed*1.15);  
  analogWrite(right_in1,0);
  analogWrite(right_in2,speed);
}

void moveForward(unsigned long time, int speed){
  while(true){
    moveForward(speed);
    if(millis() - previousMillis > time){
      previousMillis += time;
      break;
    }
  }
  brake();
}

void turnLeft(unsigned long time,int speed){
  while(true){
    turnLeft(speed);
    if(millis() - previousMillis > time){
      previousMillis += time;
      break;
    }
  }
  brake();
}

void turnRight(unsigned long time, int speed){
  while(true){
    turnRight(speed);
    if(millis() - previousMillis > time){
      previousMillis += time;
      break;  
    }  
  }
  brake();
} 

void moveBackward(unsigned long time, int speed){
  while(true){
    moveBackward(speed);
    if(millis() - previousMillis > time){
      previousMillis += time;
      break;
    }
  }
  brake();
}

void startMaze(){
  mazeSolved = false;
  firstTurn = false;
  Serial.write("Start");
  moveForward(50);
}

void justin_startMaze(){
  justin_mazeSolved = false;
}
void setMazeCompleted(){
  mazeSolved = true;
  justin_mazeSolved = true;
  brake();
}

//Bluetooth Connection and Command Setup
byte command;
void executeCommand(int command){
  switch(command){
    case 0:
      break;
    case 255:
      brake();
      break;
    case 251:
      moveForward(defined_speed);
      break;
    case 252:
      turnLeft(turn_defined_speed);
      break;
    case 253:
      turnRight(turn_defined_speed);
      break;
    case 254:
      moveBackward(defined_speed);
      break;
    case 246:
      startMaze();
      break;
    case 247:
      setMazeCompleted();
      break;
    case 248:
      justin_startMaze();
      break;
    default: // when speed is sent
      defined_speed = command;
      justin_defined_speed = command;
      break;
  }
}

long getDistance(long distance, int direct){
  if(distance > 250 || distance < 0){
    if(back > 3){     //if run getDistance() for three times
      moveBackward(150);
      back = 0;
    }
    
    switch(direct){
    case 1:
      back++;
      distance = sr04_left.Distance();
      break;
    case 2:
      back++;
      distance = sr04_front.Distance();
      break;
    case 3:
      back++;
      distance = sr04_right.Distance();
      break;
    }
  }  
  return distance;
}

void check_distance(){
  left_distance = getDistance(sr04_left.Distance(),1);
  front_distance = getDistance(sr04_front.Distance(),2);
  right_distance = getDistance(sr04_right.Distance(),3);
}

void check_wall(){
  if(front_distance<front_defined_distance){
    front_has_wall = true;
  } else {
    front_has_wall = false;
  }
  if(left_distance<left_defined_distance){
    left_has_wall = true;  
  } else {
    left_has_wall = false;
  }
  if(right_distance<right_defined_distance){
    right_has_wall = true;
  } else {
    right_has_wall = false;
  }
  if(left_distance - right_distance > tooclose_defined_distance || right_distance <= 3){
    right_tooclose = true;
  } else right_tooclose = false;
  if(right_distance - left_distance > tooclose_defined_distance || left_distance <= 3){
    left_tooclose = true;
  } else left_tooclose = false;
  if(front_distance < 10 || left_distance < 3 || right_distance < 3){
    front_tooclose = true;
  } else front_tooclose = false;
}

void deviate_check(){
  check_distance();
  check_wall();
  if(left_tooclose){
    Serial.write("Left tooclose");
    moveBackward(backward_defined_speed);
    delay(50);
    turnRight(right_defined_speed);
    delay(50);
    turnLeft(left_defined_speed);
    delay(50);
    moveForward(forward_defined_speed);
    delay(25);
  }
  if(right_tooclose){
    Serial.write("Right tooclose");
    moveBackward(backward_defined_speed);
    turnLeft(left_defined_speed);
    delay(50);
    turnRight(right_defined_speed);
    delay(50);
    moveForward(forward_defined_speed);
  }
}
void maze(){
  check_distance();
  check_wall();
  if(!firstTurn){
    if(!front_has_wall){
      moveForward(50);
    } else {
      firstTurn = true;
    }
    return;
  }
  if(leftMode){
    brake();
    delay(200);
    if(front_tooclose){
      moveBackward(200,backward_defined_speed);
    } else if(!left_has_wall){ // First rule: if there is road left
      Serial.write("First rule: left");
      moveForward(forward_defined_speed);
      delay(100);
      turnLeft(left_defined_speed);
      delay(left_defined_time);
      moveForward(forward_defined_speed);
      delay(forward_defined_time);
    } else if (!front_has_wall){ // Second rule: if there is road front
      Serial.write("Second rule: front");
      moveForward(forward_defined_speed);
      delay(50);
      deviate_check();
      } else { //Third rule: if there is no road for left and forward
      Serial.write("Third rule: right");
      turnRight(right_defined_speed);
      delay(right_defined_time);
    }
  } else {
    if(!right_has_wall){ // First rule: if there is road to right
      turnRight(right_defined_time, right_defined_speed);
      moveForward(forward_defined_time,forward_defined_speed);
    } else if (!front_has_wall){ // Second rule: if there is road forward
      moveForward(forward_defined_time,forward_defined_speed);
      delay(50);
      deviate_check();
      } else { //Third rule: if there is no road for right and forward
      turnLeft(left_defined_time,left_defined_speed);
    }
  }
}

void movement(){
  check_distance();
  if (front_distance < justin_front_defined_distance){
    brake();
    if(left_distance < justin_left_defined_distance && left_distance > 0){
      Serial.write("right rule");
      turnRight(50);
    }else{
      Serial.write("left rule");
      turnLeft(50);
    }
  }else{
    /*
    check_distance(1);
    check_distance(3);
    if((Right_Distance - Left_Distance) > tooclose_defined_distance){
      deviation_to_left(100);
    }else if((Left_Distance - Right_Distance) > tooclose_defined_distance){
      deviation_to_right(100);
    }else{
    */
    Serial.write("front rule");
      moveForward(justin_defined_speed);
    //}
  }
}

void setup() {
  Serial.begin(9600);
  // pinMode of ultrasonic sensors are defined in NewPing library itself
  pinMode(right_in1,OUTPUT);
  pinMode(right_in2,OUTPUT);
  pinMode(left_in1,OUTPUT);
  pinMode(left_in2,OUTPUT);
}

void loop() {
  if(Serial.available()){
    command = Serial.read();    
    executeCommand(command);
  }

  if(!mazeSolved){ // Zero rule: if the maze is not completed
    maze();
  }
  if(!justin_mazeSolved){
    movement();
  }
}
