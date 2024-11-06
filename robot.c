#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "globals.h"
#include "drawArena.h"
#include "robot.h"


const int SLEEPTIME = 5;

int atMarker(Robot *robot, Tile *tile){
    return tile[robot->tileIndex].type == 'm';
}

int markerCount(Robot robot){
    return robot.numMarkers;
}

void dropMarker(Robot *robot, Tile* tile){
    int tileIndex = robot->tileIndex;
    tile[tileIndex].type = 'm';
    replaceFreeTile(tile[tileIndex]);
    robot->numMarkers -= 1;
}

void pickUpMarker(Robot *robot, Tile *tile){
    //change the tile's type to 't' then redraw that tile
    int tileIndex = robot->tileIndex;
    tile[tileIndex].type = 't';
    replaceMarker(tile[tileIndex]);
    //increment num of markers the robot has
    robot->numMarkers += 1;
}

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




void right(Robot *robot){
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

void left(Robot *robot){
    switch(robot->direction){
        case 'N':
            robot->direction = 'W';
            break;
        case 'E':
            robot->direction = 'N';
            break;
        case 'S':
            robot->direction = 'E';
            break;
        case 'W': 
            robot->direction = 'S';
            break;
    }
    drawRobot(robot);
}


int onCorner(Robot *robot, Tile *tile){
    int i = robot->tileIndex;
    if(i == NUMCOLS + 1 || //top left
       i == 2 * NUMCOLS - 2 || //top right
       i == (NUMCOLS * (NUMROWS - 2) + 1) ||// bottom left
       i == (NUMCOLS * (NUMROWS - 1) -2) //bottom right
    ){
        return 1;
    }
    return 0;
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




void faceNorth(Robot *robot){
    while(robot->direction != 'N'){
        right(robot);
        sleep(SLEEPTIME);
    }
}
void faceEast(Robot *robot){
    while(robot->direction != 'E'){
        right(robot);
        sleep(SLEEPTIME);
    }
}
void faceSouth(Robot *robot){
    while(robot->direction != 'S'){
        right(robot);
        sleep(SLEEPTIME);
    }
}
void faceWest(Robot *robot){
    while(robot->direction != 'W'){
        right(robot);
        sleep(SLEEPTIME);
    }
}

//creates a data type which is a pointer to a function which takes a parameter of Robot*
typedef void(*funcPtr)(Robot*);

void pushToStack(funcPtr func, funcPtr *stack, int *topPtr){
    stack[*topPtr] = func;
    (*topPtr)++;
}

funcPtr popFromStack(funcPtr *stack, int *topPtr){
    if(*topPtr > 0){
        funcPtr popped = stack[(*topPtr) - 1];
        (*topPtr)--;
        return popped;
    } else{
        printf("tried to pop from empty stack\n");
    }
}

bool isVisited(Robot *robot, Tile *tile){
    return tile[robot->tileIndex].visited;
}

void markVisited(Robot *robot, Tile *tile, colour colour){
    background();
    tile[robot->tileIndex].visited = 1;
    setColour(colour);
    fillRect(robot->x, robot->y, GRID_SIZE, GRID_SIZE);
}

char checkAdjacentTiles(Robot *robot, Tile *tile){
    int robotIndex = robot->tileIndex;
    if((tile[robotIndex - NUMCOLS].type == 't' || tile[robotIndex - NUMCOLS].type == 'm') && !tile[robotIndex - NUMCOLS].visited){
        return 'N'; //north
    } else if((tile[robotIndex + 1].type == 't' || tile[robotIndex + 1].type == 'm') && !tile[robotIndex + 1].visited){
        return 'E'; //east
    } else if((tile[robotIndex + NUMCOLS].type == 't' || tile[robotIndex + NUMCOLS].type == 'm') && !tile[robotIndex + NUMCOLS].visited){
        return 'S'; //south
    } else if((tile[robotIndex - 1].type == 't' || tile[robotIndex - 1].type == 'm') && !tile[robotIndex - 1].visited){
        return 'W'; //west
    } else{
        return 'F'; //no qualifying tiles
    }
}


void moveToAdjacent(Robot *robot, Tile *tile, funcPtr *rtnStack, int *topRtnPtr){
    //check for the first adjacent tile i can move to
        char moveableTile = checkAdjacentTiles(robot, tile);
        switch(moveableTile){
            case 'N':
                faceNorth(robot);
                sleep(SLEEPTIME);
                forward(robot);
                sleep(SLEEPTIME);
                pushToStack(forward, rtnStack, topRtnPtr);
                pushToStack(faceSouth, rtnStack, topRtnPtr);
                break;
            case 'E':
                faceEast(robot);
                sleep(SLEEPTIME);
                forward(robot);
                sleep(SLEEPTIME);
                pushToStack(forward, rtnStack, topRtnPtr);
                pushToStack(faceWest, rtnStack, topRtnPtr);
                break;
            case 'S':
                faceSouth(robot);
                sleep(SLEEPTIME);
                forward(robot);
                sleep(SLEEPTIME);
                pushToStack(forward, rtnStack, topRtnPtr);
                pushToStack(faceNorth, rtnStack, topRtnPtr);
                break;
            case 'W':
                faceWest(robot);
                sleep(SLEEPTIME);
                forward(robot);
                sleep(SLEEPTIME);
                pushToStack(forward, rtnStack, topRtnPtr);
                pushToStack(faceEast, rtnStack, topRtnPtr);
                break;
            case 'F':
                //no moveable tiles that are unvisited, so backtrack
                //pop and run returned function

                funcPtr func = popFromStack(rtnStack, topRtnPtr);
                func(robot);
                sleep(SLEEPTIME);
                moveToAdjacent(robot, tile, rtnStack, topRtnPtr);
                break;
                //check if there's any adjacent tiles
        }
}
void startRobot(Tile *tile){
    Robot robot;
    int isValid = 0;
    // initialise robot position
    while(!isValid){
        int index = randomNum(NUMCOLS + 1, SIZE);
        if(tile[index].type == 't'){
            robot.x = tile[index].x;
            robot.y = tile[index].y;
            robot.tileIndex = index;
            isValid = 1;
        }
    }
    robot.numMarkers = 0;
    //set random direction
    char directions[] = {'N', 'E', 'S', 'W'};
    robot.direction = directions[randomNum(0, 3)];

    //draw the robot
    drawRobot(&robot);
    runRobot(&robot, tile);
    }


void runRobot(Robot *robot, Tile *tile){
    //create an array to be the stack
    const int MAXSIZE = 200;
    funcPtr *rtnStack = (funcPtr*)calloc(MAXSIZE, sizeof(funcPtr));
    int topOfRtnStack = 0;
    int *topRtnPtr = &topOfRtnStack;

    int running = 1;
    while(running){

        if(atMarker(robot, tile)){
            pickUpMarker(robot, tile);
            if(robot->numMarkers == totMarkers){
                for(int i = 0; i < SIZE; i++){
                    tile[i].visited = false;
                }
                while(!onCorner(robot, tile)){
                    if(!isVisited(robot, tile)){
                        markVisited(robot, tile, orange);
                        sleep(SLEEPTIME);
                        }
                    sleep(SLEEPTIME);
                    moveToAdjacent(robot, tile, rtnStack, topRtnPtr);
                }
                dropMarker(robot, tile);
                printf("I've successfully finished");
                running = 0;
                break;
            }

        }

        if(!isVisited(robot, tile)){
            markVisited(robot, tile, green);
            sleep(SLEEPTIME);
        }
        sleep(SLEEPTIME);
        moveToAdjacent(robot, tile, rtnStack, topRtnPtr);
    }
    free(rtnStack);
}

