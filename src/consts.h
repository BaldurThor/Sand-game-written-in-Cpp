#ifndef SAND_CONSTS_H
#define SAND_CONSTS_H

#include "SDL2/SDL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int SCREEN_PADDING = 20;

const int TICK_RATE = 1000 / 60;
const int GRID_CELL_SIZE = 2;
const int GRID_WIDTH = 320;
const int GRID_HEIGHT = 220;

const char* const NAME = "Sand Scape";

const char* const SAND_HEADER = "SAND";
const char* const GRAVEL_HEADER = "GRAVEL";
const char* const WATER_HEADER = "WATER";
const char* const WALL_HEADER = "WALL";
const char* const OIL_HEADER = "OIL";

const SDL_Color BG_COLOR = { 242, 240, 229 };
const SDL_Color HEADER_COLOR = { 69, 68, 79 };
const SDL_Color TEXT_COLOR = { 242, 240, 229 };
const SDL_Color TEXT_HOVER_COLOR = { 192, 190, 179 };
const SDL_Color SELECTED_TEXT_COLOR = { 0, 0, 0 };
const SDL_Color MENU_BUTTON_COLOR = { 0x80, 0x80, 0x80 };
const SDL_Color MENU_BUTTON_HOVER_COLOR = { 0, 0, 0 };

const char* const GRAVEL_SOUND_PATH = "assets/gravelsound.wav";
const char* const SAND_SOUND_PATH = "assets/sandsound.wav";
const char* const WATER_SOUND_PATH = "assets/watersound.wav";
const char* const OIL_SOUND_PATH = "assets/oilsound.wav";
const char* const WALL_SOUND_PATH = "assets/wallsound.wav";
const char* const MUSIC_PATH = "assets/lady-of-the-80x27s-128379.wav";
const char* const REMOVE_SOUND_PATH = "assets/removesound.wav";
const char* const LOGO_PATH = "assets/logo.png";
const char* const ICON_PATH = "assets/icon.png";
const char* const PLAY_PAUSE_PATH = "assets/playPause.png";
const char* const FONT_PATH = "assets/dogica.ttf";

const int PLAY_PAUSE_SIZE = 16;
const int PLAY_PAUSE_TEXTURE_SIZE = 32;
const int LOGO_WIDTH = 194;
const int LOGO_HEIGHT = 92;
const double LOGO_SCALE = 1.5;

const char* const RESET_TEXT = "Press R to reset";

const int TEXT_PADDING = 4;
const int BUTTON_FONT_SIZE = 20;
const int MATERIAL_TEXT_PADDING = 2;
const int MATERIAL_BUTTON_FONT_SIZE = 16;
const int HOW_TO_PLAY_FONT_SIZE = 10;

#endif