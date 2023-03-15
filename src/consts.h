#ifndef CONSTS_H
#define CONSTS_H

#include <map>

#include "materials.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int TICK_RATE = 1000 / 60;
const int GRID_CELL_SIZE = 2;
const int BRUSH_SIZE = 5; // must be odd
const int GRID_WIDTH = SCREEN_WIDTH / GRID_CELL_SIZE;
const int GRID_HEIGHT = SCREEN_HEIGHT / GRID_CELL_SIZE;

Material grid[GRID_WIDTH][GRID_HEIGHT] = { NONE };

std::map<Material, Materials_struct> materials = {
    {SAND, Materials_struct(SAND)},
    {GRAVEL, Materials_struct(GRAVEL)}
};
#endif