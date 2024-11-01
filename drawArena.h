#ifndef DRAWARENA_H
#define DRAWARENA_H
#include "globals.h"

Tile* drawArena();
void replaceMarker(Tile curTile);
void replaceFreeTile(Tile curTile);
extern int GRID_SIZE;
extern int NUMROWS;
extern int NUMCOLS;
#define SIZE (NUMROWS * NUMCOLS)


#endif