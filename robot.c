#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "globals.h"
#include "drawArena.h"


typedef struct Robot{
    int x;
    int y;
    char direction;
    int tileIndex;
} Robot;

void drawRobot(Robot *robot);


int randomNum(int min, int max){
    return rand() % (max - min + 1) + min;
}

void forward(Robot *robot, Tile *tile){
    switch(robot->direction){
        case 'N':
            robot->y -= GRID_SIZE;
            robot->tileIndex -= NUMCOLS;
            break;
        case 'E':
            robot->x += GRID_SIZE;
            robot->tileIndex += 1;
            break;
        case 'S':
            robot->y += GRID_SIZE;
            robot->tileIndex += NUMCOLS;
            break;
        case 'W':
            robot->x -= GRID_SIZE;
            robot->tileIndex -= 1;
            break;
    }
    drawRobot(robot);
}

int canMoveForward(Robot *robot, Tile *tile){
    int targetIndex;
    switch(robot->direction){
        case 'N':
            targetIndex = robot->tileIndex - NUMCOLS;
            break;
        case 'E':
            targetIndex = robot->tileIndex + 1;
            break;
        case 'S':
            targetIndex = robot->tileIndex + NUMCOLS;
            break;
        case 'W':
            targetIndex = robot->tileIndex - 1;
            break;
        default:
            return 0;
    }
    return tile[targetIndex].type == 2;
}

void drawRobot(Robot *robot){
    foreground();
    clear();
    setColour(red);
    int x = robot->x;
    int y = robot->y;
    int dir = robot->direction;
    if(dir == 'N'){
        //Facing north
        int xCoords[] = {x + GRID_SIZE/2, x, x + GRID_SIZE};
        int yCoords[] = {y, y + GRID_SIZE, y + GRID_SIZE};
        fillPolygon(3, xCoords , yCoords);
    } else if(dir == 'E'){
        //east
        int xCoords[] = {x, x + GRID_SIZE, x};
        int yCoords[] = {y, y + GRID_SIZE/2, y + GRID_SIZE};
        fillPolygon(3, xCoords , yCoords);
    } else if(dir == 'S'){
        //south
        int xCoords[] = {x, x + GRID_SIZE, x + GRID_SIZE/2};
        int yCoords[] = {y, y, y + GRID_SIZE};
        fillPolygon(3, xCoords , yCoords);
    } else{
        //west
        int xCoords[] = {x, x + GRID_SIZE, x + GRID_SIZE};
        int yCoords[] = {y + GRID_SIZE/2, y, y + GRID_SIZE};
        fillPolygon(3, xCoords , yCoords);
    }
}


void runRobot(Tile *arr){
    Robot robot;
    int isValid = 0;
    //initialise robot position
    while(!isValid){
        int index = randomNum(0, SIZE);
        if(arr[index].type == 2){
            robot.x = arr[index].x;
            robot.y = arr[index].y;
            robot.tileIndex = index;
            isValid = 1;
        }
    }
    //set random direction
    char directions[] = {'N', 'E', 'S', 'W'};
    int index = randomNum(0, 3);
    robot.direction = directions[index];

    //draw the robot
    drawRobot(&robot);

    //runs the robot
    int running = 1;
    while(running){
        if(canMoveForward(&robot, arr)){
            forward(&robot, arr);
            sleep(500);
        } else{
            running = 0;
        }

    }


}