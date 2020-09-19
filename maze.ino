#import vector

vector<int> travelled; // 0 = front, 1 = left, 2 = right, 3 = back

bool mazeSolved = false;
bool shortestpath = true;

void moveForward(int time, int speed){
  travelled.push_back(0);
}

void turnLeft(int time,int speed){
  travelled.push_back(1);
}
void turnRight(int time, int speed){
  travelled.push_back(2);
}

void shortestPathCheck(int mode){ 
  switch(mode){
    case 0:
      if(travelled.back()==0){
        travelled.pop_back();
      }  else {
        shortestpath = true;
      }
    case 1:
      if(travelled.back()==2){
        travelled.pop_back();
      } else {
        shortestpath = true;  
      }
    case 2:
      if(travelled.back()==1){
        travelled.pop_back();
      } else {
        shortestpath = true;  
      }
  }
}
void maze(bool leftMode){
  
  while(mazeSolved){
    if(leftMode){
      if(left_distance<10){
        turnLeft(2000,255);
        moveForward(1000,255);
        if(!shortestpath){
          shortestPathCheck(1);
        }
      } else if (front_distance<10){
        moveForward(100,255);
        travelled.push_back(0);
        if(!shortestpath){
          shortestPathCheck(0);  
        }
        } else {
          turnRight(2000,255);
          if(travelled.back()==2){
            shortestpath = false;
            travelled.pop_back();
            continue;
          }
          if(!shortestpath){
            shortestPathCheck(2);  
          }
        }  
    }
  }
  vector<string>::iterator it;
  for(it = travelled.begin();it!=travelled.end();it++){
    Serial.print(*it);
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  left_distance = 0;
  front_distance = 0;  
}

