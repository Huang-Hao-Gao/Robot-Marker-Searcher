#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "globals.h"

int GRID_SIZE = 30;
int MINROWCOL = 5;
int MAXROWCOL = 15;
int NUMROWS;
int NUMCOLS;
// Using #define for SIZE ensures that it always represents the current product of NUMROWS and NUMCOLS,
// even if these values are changed later in the code. This keeps SIZE consistent with their current values.
#define SIZE (NUMROWS * NUMCOLS)

int randArenaSize(){
    return randomNum(MINROWCOL, MAXROWCOL);
}

void initialiseGlobals() {
    NUMROWS = randArenaSize();
    NUMCOLS = randArenaSize();
}

//this function was generated by copilot
void printTiles(Tile *tile, int rows, int columns) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            int index = r * columns + c;
            printf("Tile at (%d, %d): x = %d, y = %d, type = %c , index = %d\n", r, c, tile[index].x, tile[index].y, tile[index].type, tile[index].index);
        }
    }
}

void drawTiles(Tile *tile){
    background();
    setColour(gray);
    for(int i = 0; i < SIZE; i++){
        int x = tile[i].x;
        int y = tile[i].y;
        char type = tile[i].type;
        if(type == 'w'){
            //wall
            setColour(blue);
            fillRect(x, y, GRID_SIZE, GRID_SIZE);
            setColour(gray);
        } else if(type == 'm'){
            //marker
            setColour(red);
            fillRect(x, y, GRID_SIZE, GRID_SIZE);
            setColour(gray);
        } else{
            //tile
            drawRect(x, y, GRID_SIZE, GRID_SIZE);
        }
    }
}


void appendArray(Tile *tile, int r, int c, Tile curTile){
    //append 3 elements
    int index = r * NUMCOLS + c;
    tile[index].x = curTile.x;
    tile[index].y = curTile.y;
    tile[index].type = curTile.type;
    tile[index].index = curTile.index;
}

//function to fill a 2d array with elements, where each element is an array with [x, y, typeOfTile]
void createTiles(Tile *tile, int rows, int columns){
    //initial x and y pos
    int x = CANVAS_WIDTH/5;
    int y = CANVAS_HEIGHT/5;
    int i = 0;

    for(int r = 0; r < rows; r++){
    
        for(int c = 0; c < columns; c++){
            //top wall
            if(r == 0 || r == rows - 1){
                Tile curTile = {x, y, 'w', i};
                appendArray(tile, r, c, curTile);
                x += GRID_SIZE;
                i++;
            }
            else{ 
                if(c == 0 || c == columns - 1){
                    //left and right wall
                    Tile curTile = {x, y, 'w', i};
                    appendArray(tile, r, c, curTile);
                    i++;
                } else{
                    //tiles between walls
                    Tile curTile = {x, y, 't', i};
                    appendArray(tile, r, c, curTile);
                    i++;
                }
                x += GRID_SIZE;
            }
        }
        //move to next row
        x = CANVAS_WIDTH/5;
        y += GRID_SIZE;
    }

    //randomise placement of marker
    int isMarker = 0;
    while(!isMarker){
        int index = randomNum(MINROWCOL, MAXROWCOL);
        //check if any adjacent tile is a wall
        if((tile[index - NUMCOLS].type == 'w' || 
            tile[index - 1].type == 'w' || 
            tile[index + 1].type == 'w' || 
            tile[index + NUMCOLS].type == 'w') &&
            tile[index].type == 't'){
                tile[index].type = 'm';
                isMarker = 1;
        }
    }
}

Tile* drawArena(){
    initialiseGlobals(); // Initialise NUMROWS and NUMCOLS
    //allocate memory for an array of structs
    Tile *arenaTiles = (Tile*)malloc(SIZE * sizeof(Tile));

    createTiles(arenaTiles, NUMROWS, NUMCOLS);
    // printTiles(arenaTiles, NUMROWS, NUMCOLS);
    drawTiles(arenaTiles);
    return arenaTiles;
}

