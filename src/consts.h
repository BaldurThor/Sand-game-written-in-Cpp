#ifndef SAND_CONSTS_H
#define SAND_CONSTS_H

#include "SDL2/SDL.h"

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

const char* const LOGO_PATH = "bin/assets/logo.png";
const char* const ICON_PATH = "bin/assets/icon.png";
const int LOGO_WIDTH = 194;
const int LOGO_HEIGHT = 92;
const double LOGO_SCALE = 1.5;
const int LOGO_WIDTH_SCALED = LOGO_WIDTH * LOGO_SCALE;
const int LOGO_HEIGHT_SCALED = LOGO_HEIGHT * LOGO_SCALE;
const SDL_Rect LOGO_RECT = { (SCREEN_WIDTH/2) -  (LOGO_WIDTH_SCALED/2), (SCREEN_HEIGHT/2) - (int)(LOGO_HEIGHT_SCALED * LOGO_SCALE), LOGO_WIDTH_SCALED, LOGO_HEIGHT_SCALED };

const char* const RESET_TEXT = "Press R to reset";

const int BUTTON_FONT_SIZE = 20;
const SDL_Color MENU_BUTTON_COLOR = { 0x80, 0x80, 0x80 };
const SDL_Color MENU_BUTTON_HOVER_COLOR = { 0, 0, 0 };

const SDL_Rect START_BUTTON_RECT = { (SCREEN_WIDTH/2) + (3 * BUTTON_FONT_SIZE) - (int)(5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2) - 2 * BUTTON_FONT_SIZE, 5 * BUTTON_FONT_SIZE, BUTTON_FONT_SIZE };
const SDL_Rect HOW_TO_PLAY_BUTTON_RECT = { (SCREEN_WIDTH/2) - (int)(5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2) - BUTTON_FONT_SIZE, 11 * BUTTON_FONT_SIZE, BUTTON_FONT_SIZE };
const SDL_Rect EXIT_BUTTON_RECT = { (SCREEN_WIDTH/2) + (int)(3.5 * BUTTON_FONT_SIZE) - (int)(5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2), 4 * BUTTON_FONT_SIZE, BUTTON_FONT_SIZE };

#endif