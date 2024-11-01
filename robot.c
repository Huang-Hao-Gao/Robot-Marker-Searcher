#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "globals.h"
#include "drawArena.h"
#include "robot.h"




void forward(Robot *robot){
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
    return tile[targetIndex].type == 't' || tile[targetIndex].type == 'm';
}


int atMarker(Robot *robot, Tile *tile){
    return tile[robot->tileIndex].type == 'm';
}


void right(Robot *robot){
    //rotate 90 degrees clockwise
    switch(robot->direction){
        case 'N':
            robot->direction = 'E';
            break;
        case 'E':
            robot->direction = 'S';
            break;
        case 'S':
            robot->direction = 'W';
            break;
        case 'W': 
            robot->direction = 'N';
            break;
    }
    drawRobot(robot);
}


void drawRobot(Robot *robot){
    foreground();
    clear();
    setColour(cyan);
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


void runRobot(Tile *tile){
    Robot robot;
    int isValid = 0;
    //initialise robot position
    while(!isValid){
        int index = randomNum(0, SIZE);
        if(tile[index].type == 't'){
            robot.x = tile[index].x;
            robot.y = tile[index].y;
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
        if(atMarker(&robot, tile)){
            running = 0;
        }
        else if(canMoveForward(&robot, tile)){
            forward(&robot);
            sleep(50);
        } else{
            right(&robot);
            sleep(50);
        }

    }


}