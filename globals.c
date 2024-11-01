#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

//The maximum canvas size is 2500,1500.
const int CANVAS_WIDTH = 1000;
const int CANVAS_HEIGHT = 800;
int randomNum(int min, int max){
    return rand() % (max - min + 1) + min;
}
