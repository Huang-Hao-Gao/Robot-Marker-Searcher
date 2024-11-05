#ifndef DRAWARENA_H
#define DRAWARENA_H
#include "globals.h"

Tile* drawArena();
void replaceMarker(Tile curTile);
void replaceFreeTile(Tile curTile);
void drawOneTile(int x, int y, colour colour);
extern const int GRID_SIZE;
extern const int totMarkers;
extern int NUMROWS;
extern int NUMCOLS;
#define SIZE (NUMROWS * NUMCOLS)


#endif