

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "globals.h"
#include "drawArena.h"
#include <time.h>


typedef struct Robot{
    int x;
    int y;
    char *direction;
} Robot;


int randomNum(int min, int max){
    return rand() + min % (max - min + 1);
}




void runRobot(Tile *arr){
    Robot robot;
    //initialise it's x, y and direction
    // ensures that the sequence of random numbers is different each time
    srand(time(NULL));


    //1 is wall, 2 is tile, 3 is marker, 4 is obstacle
    int isValid = 0;

    //initialise robot values
    while(!isValid){
        int index = randomNum(0, 40);
        if(arr[index].type == 2){
        robot.x = arr[index].x;
        robot.y = arr[index].y;
        isValid = 1;
    }
    }

    //draw the robot
}