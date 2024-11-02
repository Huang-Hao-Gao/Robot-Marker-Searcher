// Stage 5: Add one or more obstacles and markers at random positions, with the robot finding 
// and picking up all the markers then going to a corner and dropping the markers. The robot 
// algorithm should be as resilient as possible, such that the robot cannot get stuck in a never-
// ending cycle of movement due to the way that obstacles are positioned.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphics.h"
#include "globals.h"
#include "drawArena.h"
#include "robot.h"



int main(){
    srand(time(NULL));
    setWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    Tile *arrPointer = drawArena();
    startRobot(arrPointer);
    

    return 0;
}