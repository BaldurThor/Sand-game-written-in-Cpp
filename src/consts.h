#ifndef CONSTS_H
#define CONSTS_H

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_PADDING = 20;

const int TICK_RATE = 1000 / 60;
const int GRID_CELL_SIZE = 2;
const int BRUSH_SIZE = 5; // must be odd
const int GRID_WIDTH = SCREEN_WIDTH / GRID_CELL_SIZE;
const int GRID_HEIGHT = (SCREEN_HEIGHT - (2 * SCREEN_PADDING)) / GRID_CELL_SIZE;

enum Material {
    NONE,
    SAND,
    GRAVEL,
    WATER,
    WALL,
};



#endif