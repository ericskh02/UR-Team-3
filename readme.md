# Documentation for UR Team 3 Robot Program

## Functions For Bluetooth Connection:
executeCommand(String command); execute a function

## Functions For Ultrasonic Sensor Reading:
getFrontDistance(); return int in cm\
getLeftDistance();  return int in cm

## Functions For Robot Movement:

### 1) Perform forward movement
moveForward(int speed);\
moveForward(unsigned long time,int speed);

### 2) Perform left turn movement
turnLeft(int speed);\
turnLeft(unsigned long time, int speed);

### 3) Perform right turn movement
turnRight(int speed);\
turnRight(unsigned long time, int speed);

### 4) Perform backward movement
moveBackward(int speed);\
moveBackward(unsigned long time, int speed);

### 5) Stop the robot from moving
brake();\
brake(unsigned long time);

## Functions For Maze:
### 1) Starts the maze algorithm
startMaze(bool leftMode);
### 2) Notify the robot that the maze is completed and the maze algorithm can be stopped
setMazeCompleted();
