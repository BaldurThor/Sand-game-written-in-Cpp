#ifndef SAND_CONSTS_H
#define SAND_CONSTS_H

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_PADDING = 20;

const int TICK_RATE = 1000 / 60;
const int GRID_CELL_SIZE = 2;
const int GRID_WIDTH = SCREEN_WIDTH / GRID_CELL_SIZE;
const int GRID_HEIGHT = (SCREEN_HEIGHT - (2 * SCREEN_PADDING)) / GRID_CELL_SIZE;

const char* const SAND_HEADER = "SAND";
const char* const GRAVEL_HEADER = "GRAVEL";
const char* const WATER_HEADER = "WATER";
const char* const WALL_HEADER = "WALL";
const char* const OIL_HEADER = "OIL";

#endif