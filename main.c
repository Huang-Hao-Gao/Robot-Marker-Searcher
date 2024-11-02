// Stage 4: Allow the marker to be placed anywhere at a random position inside the arena, with 
// the robot starting at a random position and direction to find it, and then going to any corner 
// to drop the marker. A more complex algorithm will be needed to move the robot around. 

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