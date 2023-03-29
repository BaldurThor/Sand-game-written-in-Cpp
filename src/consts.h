#ifndef SAND_CONSTS_H
#define SAND_CONSTS_H

#include "SDL2/SDL.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

const int SCREEN_PADDING = 40;

const int TICK_RATE = 1000 / 60;
const int GRID_CELL_SIZE = 4;
const int GRID_WIDTH = SCREEN_WIDTH / GRID_CELL_SIZE;
const int GRID_HEIGHT = (SCREEN_HEIGHT - (2 * SCREEN_PADDING)) / GRID_CELL_SIZE;

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

const char* const GRAVEL_SOUND_PATH = "bin/assets/gravelsound.wav";
const char* const SAND_SOUND_PATH = "bin/assets/sandsound.wav";
const char* const WATER_SOUND_PATH = "bin/assets/watersound.wav";
const char* const OIL_SOUND_PATH = "bin/assets/oilsound.wav";
const char* const WALL_SOUND_PATH = "bin/assets/wallsound.wav";
const char* const MUSIC_PATH = "bin/assets/lady-of-the-80x27s-128379.wav";
const char* const REMOVE_SOUND_PATH = "bin/assets/removesound.wav";

const char* const LOGO_PATH = "bin/assets/logo.png";
const char* const ICON_PATH = "bin/assets/icon.png";
const char* const PLAY_PAUSE_PATH = "bin/assets/playPause.png";
const int PLAY_PAUSE_SIZE = 32;
const int PLAY_PAUSE_TEXTURE_SIZE = 32;
const int LOGO_WIDTH = 194;
const int LOGO_HEIGHT = 92;
const double LOGO_SCALE = 2.5;
const int LOGO_WIDTH_SCALED = LOGO_WIDTH * LOGO_SCALE;
const int LOGO_HEIGHT_SCALED = LOGO_HEIGHT * LOGO_SCALE;
const SDL_Rect LOGO_RECT = { (SCREEN_WIDTH/2) -  (LOGO_WIDTH_SCALED/2), (SCREEN_HEIGHT/4) - (LOGO_HEIGHT_SCALED/2), LOGO_WIDTH_SCALED, LOGO_HEIGHT_SCALED };

const char* const RESET_TEXT = "Press R to reset";


const int TEXT_PADDING = 8;
const int BUTTON_FONT_SIZE = 40;
const int MATERIAL_BUTTON_FONT_SIZE = 32;
const int HOW_TO_PLAY_FONT_SIZE = 20;

const int HOW_TO_PLAY_WIDTH = 64 * HOW_TO_PLAY_FONT_SIZE;
const int HOW_TO_PLAY_HEIGHT = 16 * HOW_TO_PLAY_FONT_SIZE;

const SDL_Rect START_BUTTON_RECT = { (SCREEN_WIDTH/2) + (3 * BUTTON_FONT_SIZE) - (int)(5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2) - 2 * BUTTON_FONT_SIZE, 5 * BUTTON_FONT_SIZE, BUTTON_FONT_SIZE };
const SDL_Rect HOW_TO_PLAY_BUTTON_RECT = { (SCREEN_WIDTH/2) - (int)(5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2) - BUTTON_FONT_SIZE, 11 * BUTTON_FONT_SIZE, BUTTON_FONT_SIZE };
const SDL_Rect EXIT_BUTTON_RECT = { (SCREEN_WIDTH/2) + (int)(3.5 * BUTTON_FONT_SIZE) - (int)(5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2), 4 * BUTTON_FONT_SIZE, BUTTON_FONT_SIZE };
const SDL_Rect SAND_BUTTON_RECT = { 4, 4, 4 * MATERIAL_BUTTON_FONT_SIZE, MATERIAL_BUTTON_FONT_SIZE };
const SDL_Rect GRAVEL_BUTTON_RECT = { 4 + MATERIAL_BUTTON_FONT_SIZE * 5, 4, 6 * MATERIAL_BUTTON_FONT_SIZE, MATERIAL_BUTTON_FONT_SIZE };
const SDL_Rect WATER_BUTTON_RECT = { 4 + MATERIAL_BUTTON_FONT_SIZE * 12, 4, 5 * MATERIAL_BUTTON_FONT_SIZE, MATERIAL_BUTTON_FONT_SIZE };
const SDL_Rect OIL_BUTTON_RECT = { 4 + MATERIAL_BUTTON_FONT_SIZE * 18, 4, 3 * MATERIAL_BUTTON_FONT_SIZE, MATERIAL_BUTTON_FONT_SIZE };
const SDL_Rect WALL_BUTTON_RECT = { 4 + MATERIAL_BUTTON_FONT_SIZE * 22, 4, 4 * MATERIAL_BUTTON_FONT_SIZE, MATERIAL_BUTTON_FONT_SIZE };

const SDL_Rect MUSIC_BUTTON_RECT = {SCREEN_WIDTH - SCREEN_PADDING + ((SCREEN_PADDING - PLAY_PAUSE_SIZE)/2), SCREEN_HEIGHT - SCREEN_PADDING + ((SCREEN_PADDING - PLAY_PAUSE_SIZE)/2), PLAY_PAUSE_SIZE, PLAY_PAUSE_SIZE};

const SDL_Rect GRID_BUTTON_RECT = {0, SCREEN_PADDING, SCREEN_WIDTH, SCREEN_HEIGHT - (2 * SCREEN_PADDING)};


#endif