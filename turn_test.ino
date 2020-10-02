unsigned long previousMillis = 0;

//Motor Setup
#define left_in1 10
#define left_in2 11
#define right_in1 6
#define right_in2 9

int left_defined_speed = 50;
int right_defined_speed = 50;  

int left_defined_time = 200;
int right_defined_time = 200;

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
  analogWrite(left_in2,speed);  
  analogWrite(right_in1,0);
  analogWrite(right_in2,speed);
}

void moveForward(unsigned long time, int speed){
  while(true){
    moveForward(speed);
    if(millis() - previousMillis > time){
      previousMillis += time;
      brake();
      break;
    }
  }
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

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  turnLeft(left_defined_time,left_defined_speed);
  delay(200);
  brake();
  delay(1000);
  
}
