    // Basic Stage 1: Display a basic rectangular arena in the drawing window, with a surrounding
    // wall and the tile grid displayed inside the walls. Place a marker in a position next to a wall.


#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

const int GRID_SIZE = 30;

//The maximum canvas size is 2500,1500.
const int CANVAS_WIDTH = 1000;
const int CANVAS_HEIGHT = 800;

const int numRows = 5;
const int numColumns = 8;
const int size = numRows * numColumns;

typedef struct Tile{
    int x;
    int y;
    int type;
} Tile;


void printTiles(Tile *arr, int rows, int columns) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            int index = r * columns + c;
            printf("Tile at (%d, %d): x = %d, y = %d, type = %d\n", r, c, arr[index].x, arr[index].y, arr[index].type);
        }
    }
}

void appendArray(Tile *arr, int r, int c, Tile tile){
    //append 3 elements
    int index = r * 8 + c;
    arr[index].x = tile.x;
    arr[index].y = tile.y;
    arr[index].type = tile.type;
}

//function to fill a 2d array with elements, where each element is an array with [x, y, typeOfTile]
void createTiles(Tile *arr, int rows, int columns){
    //initial x and y pos
    int x = CANVAS_WIDTH/5;
    int y = CANVAS_HEIGHT/5;
    int i = 0;

    //1 is wall, 2 is tile
    for(int r = 0; r < rows; r++){
    
        for(int c = 0; c < columns; c++){
            //top wall
            if(r == 0 || r == rows - 1){
                Tile tile = {x, y, 1};
                appendArray(arr, r, c, tile);
                x += GRID_SIZE;
            }
            else{
                //every row inbetween   
                if(c == 0 || c == columns - 1){
                    //left and right wall
                    Tile tile = {x, y, 1};
                    appendArray(arr, r, c, tile);
                } else{
                    //tiles between
                    Tile tile = {x, y, 2};
                    appendArray(arr, r, c, tile);
                }
                x += GRID_SIZE;
            }
        }
        //move to next row
        x = CANVAS_WIDTH/5;
        y += GRID_SIZE;
    }


}

void drawArena(){

    //2D array
    //5 rows by 8 columns
    // int arenaTiles[40][3];
    

    //allocate memory for an array of structs
    Tile *arenaTiles = (Tile*)malloc(size * sizeof(Tile));

    createTiles(arenaTiles, 5, 8);
    printTiles(arenaTiles, numRows, numColumns);
}


int main(){
    setWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    drawArena();
    




    return 0;
}