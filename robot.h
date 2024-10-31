#ifndef ROBOT_H
#define ROBOT_H
#include "globals.h"

typedef struct Robot{
    int x;
    int y;
    char direction;
    int tileIndex;
} Robot;

void runRobot(Tile *arr);
void drawRobot(Robot *robot);


#endif