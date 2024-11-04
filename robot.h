#ifndef ROBOT_H
#define ROBOT_H
#include "globals.h"

typedef struct Robot{
    int x;
    int y;
    char direction;
    int tileIndex;
    int numMarkers;
} Robot;

void startRobot(Tile *tile);
void drawRobot(Robot *robot);
void runRobot(Robot *robot, Tile *tile);

#endif