// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

extern const int CANVAS_WIDTH;
extern const int CANVAS_HEIGHT;
extern const int GRID_SIZE;
extern const int NUMROWS;
extern const int NUMCOLS;
extern const int SIZE;

typedef struct Tile{
    int x;
    int y;
    int type;
    int index;
} Tile;


#endif // GLOBALS_H

//the use of header guards, like the #ifndef GLOBALS_H, #define GLOBALS_H and #endif in this example, are used to prevent the header file from being included multiple times, which can cause errors during compilation.