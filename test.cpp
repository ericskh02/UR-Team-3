#include <iostream>
#include <string>
using namespace std;

int mazeX = 10; // length of maze (p.s. remember to change the size of maze array)
int mazeY = 10; // width of maze (p.s. remember to change the size of maze array)

int maze [15][15]; // map information of the maze (0=Road,1=Wall,2=Start position,3=Finish position)

int posX = 0; // X coordinate of robot position
int posY = 0; // Y coordinate of robot position

int endPosX = 0; // X coordinate of finish position
int endPosY = 0; // Y coordinate of finish position

int facing = 0; // Direction robot currently facing (0=Forward,1=Rightward,2=Backward,3=Leftward)
int direction = 0; // Direction robot moves (0=Forward,1=Leftward/Rightward depends on setting)

bool isLeftwardMode = true;

void inputMaze(){
    cout<<"Please input the map of maze"<<endl;
    string temp;
    for(int i = 0;i<mazex;i++){
        cin>>temp;
        if(temp.compare("end") == 0){
            break;
        }
        for(int j = 0;j<mazey;j++){
            cout<<temp;
            maze[i][j] = (int) temp[j]-48; // Converts input to maze
            if(maze[i][j]==2){
                posX = i;
                posY = j;
            }
            if(maze[i][j]==3){
                endPosX = i;
                endPosY = j;
            }
        }
    }
    cout<<"Input completed."<<endl;
    cout<<"Starting position is ("<<posX<<","<<posY<<")."<<endl;
    cout<<"Finish position is ("<<endPosX<<","<<endPosY<<""<<endl;
}

void move(int direction){
    int facing = facing;
}

void checkRoute(){
    switch(direction){
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
}

void escapeMaze(){
    cout<<"Escaping maze"<<endl; // Starting to escape
    bool escaped = false;
    while(!escaped){
        if(maze[posX][posY]==3){
            escaped = true;
            continue;
        }
        checkRoute();
    }
}

int main(){
    inputMaze(); // Starts the input process of maze map 
    escapeMaze(); // Starts the maze escape algorithm
    cout<<"Maze completed!"<<endl; // Maze completed
    return 0;
}
