#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "globals.h"
#include "drawArena.h"
#include "robot.h"


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


void startRobot(Tile *tile){
    Robot robot;
    int isValid = 0;
    //initialise robot position
    // while(!isValid){
    //     int index = randomNum(0, SIZE);
    //     if(tile[index].type == 't'){
    //         robot.x = tile[index].x;
    //         robot.y = tile[index].y;
    //         robot.tileIndex = index;
    //         isValid = 1;
    //     }
    // }
    int index = NUMCOLS * (NUMROWS - 2) + 1;
    robot.x = tile[index].x;
    robot.y = tile[index].y;
    robot.tileIndex = index;
    robot.numMarkers = 0;
    //set random direction
    char directions[] = {'N', 'E', 'S', 'W'};
    robot.direction = 'N';

    //draw the robot
    drawRobot(&robot);
    runRobot(&robot, tile);
    }

//creates a data type which is a pointer to a function which takes a parameter of Robot*
typedef void(*funcPtr)(Robot*);

void pushToStack(funcPtr func, funcPtr *stack, int *topPtr){
    stack[*topPtr] = func;
    *topPtr++;
}

funcPtr popFromStack(funcPtr *stack, int *topPtr){
    if(*topPtr > 0){
        funcPtr popped = stack[*topPtr - 1];
        *topPtr--;
        return popped;
    } else{
        printf("tried to pop from empty stack\n");
    }
}

bool visited(Robot *robot, Tile *tile){
    return tile[robot->tileIndex].visited;
}

void faceNorth(Robot *robot){
    while(robot->direction != 'N'){
        right(robot);
    }
}
void faceEast(Robot *robot){
    while(robot->direction != 'E'){
        right(robot);
    }
}
void faceSouth(Robot *robot){
    while(robot->direction != 'S'){
        right(robot);
    }
}
void faceWest(Robot *robot){
    while(robot->direction != 'W'){
        right(robot);
    }
}

void runRobot(Robot *robot, Tile *tile){
    int running = 1;
    int sleepTime = 20;

    //create an array to be the stack
    const int MAXSIZE = 200;
    funcPtr *stack = (funcPtr*)malloc(MAXSIZE * sizeof(funcPtr));
    int topOfStack = 0;
    int *topPtr = &topOfStack;


    // pushToStack(forward, stack, topPtr);
    // if(canMoveForward(robot, tile)){
    //     forward(robot);
    // } else{
    //     right(robot);
    //     right(robot);
    // }
    // while(running){
    //     if(!visited){
    //         tile[robot->tileIndex].visited = true;
    //     }
    //     if(atMarker(robot, tile)){
    //         pickUpMarker(robot, tile);
    //     }

    //     funcPtr nextMove = popFromStack(stack, topPtr);
    //     if(nextMove == forward && canMoveForward(robot, tile) || nextMove != forward){
    //         nextMove(robot);

    //         int index = robot->tileIndex;
    //         //check if adjacent tiles are able to be moved into and are unvisited

    //     }
    // }


    REMEMBER THAT I'M ON THE simple-dfs branch!!!!!!!!!!!!!!!!!!!!!!!!
    I NEED TO CHECKOUT MAIN WHEN I FIGURE OUT HOW TO DO THE ALGORITHM

}