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

//Bluetooth Connection Setup
String command;

//Motor Setup
#define motor1_in1 6
#define motor1_in2 9
#define motor2_in1 10
#define motor2_in2 11

//Time delay setup
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

//Maze
bool mazeSolved = false;

//Ultrasonic Sensor Reading
int getFrontDistance(){
  return front_distance;
}

int getLeftDistance(){
  return left_distance;  
}
//Movement of Robot
void stop(){
  analogWrite(motor1_in1,0);
  analogWrite(motor1_in2,0);
  analogWrite(motor2_in1,0);
  analogWrite(motor2_in2,0);  
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
  stop();
}

void turnLeft(unsigned long time,int speed){
  previousMillis = 0;
  while(true){
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
  stop();
}

void turnRight(unsigned long time, int speed){
  previousMillis = 0;
  while(true){
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
  stop();
} 

void moveBackward(unsigned long time, int speed){
  unsigned long previousMillis = 0;
  while(true){
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
  stop();
}

void startMaze(bool leftMode){
  mazeSolved = false;
  while(!mazeSolved){
    if(leftMode){
      if(left_distance>=30){ // First rule: if there is road to left
        turnLeft(2000,25);
        moveForward(1000,25);
      } else if (front_distance<=8){ // Second rule: if there is road forward
        moveForward(100,25);
        } else { //Third rule: if there is no road for left and forward
          turnRight(2000,25);
        }  
    }
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
  delay(1000);
  front_distance = ultrasonic1.ping_cm();
  left_distance = ultrasonic2.ping_cm();
  Serial.print("Ping Sensor1: ");
  Serial.println(front_distance);
  Serial.print("Ping Sensor2: ");
  Serial.println(left_distance);

  if(Serial.available()){
    command = Serial.readStringUntil('\n');
    if(command.equals("hello")){
      Serial.println("test");
    } else {
      Serial.println(command);
    }
  }
}
