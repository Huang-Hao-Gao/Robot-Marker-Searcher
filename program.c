    // Basic Stage 1: Display a basic rectangular arena in the drawing window, with a surrounding
    // wall and the tile grid displayed inside the walls. Place a marker in a position next to a wall.


#include <stdio.h>
#include "graphics.h"

const int GRID_SIZE = 30;

//The maximum canvas size is 2500,1500.
const int CANVAS_WIDTH = 1000;
const int CANVAS_HEIGHT = 800;


//function to fill a 2d array with elements, where each element is an array with [x, y, typeOfTile]
void fillTiles(int *arr, int rows, int columns){
    int size = rows * columns;
    background();

    //initial position to draw tiles
    int x = CANVAS_WIDTH/4;
    int y = CANVAS_HEIGHT/4;
    int i = 0;

    //1 is wall, 2 is tile
    for(int r = 0; r < rows; r++){
    
        for(int c = 0; c < columns; c++){
            //top wall
            if(r == 0){
                appendArray(x, y, 1)
            }
            //every row inbetween

            //bottom wall
        }
    }


}

void drawArena(){

    //Display the arena using lines and squares, with a value used to represent the content of each square (wall, empty, marker, obstacle, home).
    // The arena can be stored as a 2D array in the program, where each array element
    // represents a tile and holds a value denoting whether the tile is empty or contains a
    // wall, obstacle or marker

    //2D array
    //5 rows by 8 columns
    int arenaTiles[40][3];
    fillTiles(arenaTiles, 5, 8);

    background();
    //from now on everything is being drawn on background
    setColour(gray);
    drawRect(CANVAS_WIDTH/2 - GRID_SIZE, CANVAS_HEIGHT/2 - GRID_SIZE, GRID_SIZE, GRID_SIZE);

}


int main(){
    setWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);

    drawArena();





    return 0;
}