// Basic Stage 2: Display a robot and animate it so that it moves around, finds the marker and 
// stops. This can use the basic find and follow the wall algorithm. The robot should start from 
// some random position and direction inside the arena that is not next to a wall.

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

#include "globals.h"
#include "drawArena.h"
#include "robot.h"



int main(){
    setWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    Tile *arrPointer = drawArena();
    void runRobot(arrPointer);
    

    return 0;
}