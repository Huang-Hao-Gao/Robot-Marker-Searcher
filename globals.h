// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

extern const int CANVAS_WIDTH;
extern const int CANVAS_HEIGHT;

typedef struct Tile{
    int x;
    int y;
    char type;
    int index;
} Tile;

int randomNum(int min, int max);

#endif // GLOBALS_H

//the use of header guards, like the #ifndef GLOBALS_H, #define GLOBALS_H and #endif in this example, are used to prevent the header file from being included multiple times, which can cause errors during compilation.