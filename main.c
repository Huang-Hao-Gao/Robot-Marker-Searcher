    // Basic Stage 1: Display a basic rectangular arena in the drawing window, with a surrounding
    // wall and the tile grid displayed inside the walls. Place a marker in a position next to a wall.


#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

#include "globals.h"
#include "drawArena.h"




int main(){
    setWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    Tile *arrPointer = drawArena();
    

    return 0;
}