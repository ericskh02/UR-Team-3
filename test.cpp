#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h> // for time delay
using namespace std;

int maze[20][20]; // saves the map information of the maze (Value: 0=Road,1=Wall,2=Start position,3=Finish position)
string travelled = "S"; // saves the route travelled
string shortest = ""; // saves the shortest route found

int posX = 0; // X coordinate of robot position
int posY = 0; // Y coordinate of robot position

int endPosX = 0; // X coordinate of finish position
int endPosY = 0; // Y coordinate of finish position

int facing = 3; // Direction robot currently facing (0=Forward,1=Rightward,2=Backward,3=Leftward)
int direction = 0; // Direction robot moves (0=Forward,1=Leftward/Rightward depends on setting)

bool isLeftwardMode = true; // true = always follow left, false = always follow right

void inputMaze() {
    fstream infile;
    string filename = "test.txt";
    infile.open(filename.c_str());
    if (infile.fail())
    {
        cerr << "Could not open file: " << filename << endl;
        return;
    }
    if (infile.is_open()) {   //checking whether the file is open
        cout << "File test.txt successfully opened, now reading..." << endl;
        string temp;
        int i = 0;
        while (getline(infile, temp)) { //read map information from maze.txt
            if (temp.compare("END") == 0) {
                break;
            }
            for (int j = 0; j < temp.length(); j++) {
                maze[i][j] = (int)temp[j] - 48; // Converts input to maze
                if (maze[i][j] == 2) {
                    posX = i;
                    posY = j;
                }
                if (maze[i][j] == 3) {
                    endPosX = i;
                    endPosY = j;
                }
            }
            i++;
        }
        infile.close();
    }
    cout << "Input completed." << endl;
    cout << "Starting position is (" << posX << "," << posY << ")." << endl;
    cout << "Exit position is (" << endPosX << "," << endPosY << ")." << endl;
}

void changeFacing(bool turnLeft) {
    if (turnLeft) {
        facing = (facing + 3) % 4;
        travelled += 'L';
    }
    else {
        facing = (facing + 1) % 4;
        travelled += 'R';
    }
}

void moveForward(int frontX, int frontY) {
    posX = frontX;
    posY = frontY;
    if ('F'==travelled.back()) {
        return;
    } else {
        travelled += 'F';
    }
}


void checkRoute() {
    int frontX = posX, leftX = posX, rightX = posX;
    int frontY = posY, leftY = posY, rightY = posY;        
    switch (facing) { // depends on direction the robot is facing
    case 0:
        ++frontY;
        --leftX;
        ++rightX;
        break;
    case 1:
        ++frontX;
        ++leftY;
        --rightY;
        break;
    case 2:
        --frontY;
        ++leftX;
        --rightX;
        break;
    case 3:
        --frontX;
        --leftY;
        ++rightY;
        break;
    }
    if(isLeftwardMode){
        if (maze[leftX][leftY] != 1) { // if not a wall but is a road of exit
            changeFacing(true);
            moveForward(leftX, leftY);
        }
        else if (maze[frontX][frontY] != 1) {
            moveForward(frontX, frontY);
        }
        else {
            changeFacing(false);
        }
    } else {
        if(maze[rightX][rightY] != 1){
            changeFacing(false);
        } else if(maze[frontX][frontY] != 1){
            moveForward(frontX,frontY);
        } else {
            changeFacing(true);
        }
    }
}

void escapeMaze() {
    cout << "Escaping maze" << endl; // Starting to escape
    bool escaped = false;
    while (!escaped) {
        if (maze[posX][posY] == 3) {
            escaped = true;
            continue;
        }
        checkRoute();
    }
    cout << endl << "Maze completed!" << endl; // Maze completed
}

void printRoute() {
    cout << "Printing route: " << endl;
    for (auto r : travelled) {
        switch (r) {
            case 'F':
                cout << "Go Forward" << endl;
                break;
            case 'L':
                cout << "Turn Left" << endl;
                break;
            case 'R':
                cout << "Turn Right" << endl;
                break;
            case 'S':
                cout << "Start" << endl;
        }
    }
    cout << endl;
}

int main() {
    inputMaze(); // Starts the input process of maze map
    escapeMaze(); // Starts the maze escape algorithm
    printRoute();
    return 0;
}
