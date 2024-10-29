#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "globals.h"




//this function was generated by copilot
void printTiles(Tile *arr, int rows, int columns) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            int index = r * columns + c;
            printf("Tile at (%d, %d): x = %d, y = %d, type = %d\n", r, c, arr[index].x, arr[index].y, arr[index].type);
        }
    }
}

void drawTiles(Tile *arr){
    background();
    setColour(gray);
    for(int i = 0; i < SIZE; i++){
        int x = arr[i].x;
        int y = arr[i].y;
        int type = arr[i].type;
        if(type == 1){
            setColour(blue);
            fillRect(x, y, GRID_SIZE, GRID_SIZE);
            setColour(gray);
        } else{
            drawRect(x, y, GRID_SIZE, GRID_SIZE);
        }
    }
}


void appendArray(Tile *arr, int r, int c, Tile tile){
    //append 3 elements
    int index = r * NUMCOLS + c;
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
                if(c == 0 || c == columns - 1){
                    //left and right wall
                    Tile tile = {x, y, 1};
                    appendArray(arr, r, c, tile);
                } else{
                    //tiles between walls
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

Tile* drawArena(){
    //allocate memory for an array of structs
    Tile *arenaTiles = (Tile*)malloc(SIZE * sizeof(Tile));

    createTiles(arenaTiles, NUMROWS, NUMCOLS);
    // printTiles(arenaTiles, numRows, numColumns);
    drawTiles(arenaTiles);
    printf("%p", arenaTiles);
    return arenaTiles;
}

