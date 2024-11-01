// Stage 3: Add the code to create a rectangular arena of random size
// with a marker placed at a random position next to a wall. 
// The robot starts at a random position and direction inside the arena, finds and picks up the marker, then goes to any corner, drops the marker and stops
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