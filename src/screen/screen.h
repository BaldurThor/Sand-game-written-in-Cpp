#ifndef SAND_SCREEN_H
#define SAND_SCREEN_H

#include "SDL2/SDL.h"

#include "../consts.h"

struct Screen {
    int width = SCREEN_WIDTH;
    int height = SCREEN_HEIGHT;
    int padding = SCREEN_PADDING;
    int grid_cell_size = GRID_CELL_SIZE;
    int play_pause_size = PLAY_PAUSE_SIZE;

    double logo_scale = LOGO_SCALE;
    int logo_width_scaled = LOGO_WIDTH * logo_scale;
    int logo_height_scaled = LOGO_HEIGHT * logo_scale;

    int text_padding = TEXT_PADDING;
    int button_font_size = BUTTON_FONT_SIZE;
    int material_text_padding = MATERIAL_TEXT_PADDING;
    int material_button_font_size = MATERIAL_BUTTON_FONT_SIZE;
    int how_to_play_font_size = HOW_TO_PLAY_FONT_SIZE;

    int how_to_play_width = 64 * how_to_play_font_size;
    int how_to_play_height = 16 * how_to_play_font_size;

    SDL_Rect logo_rect = { (width/2) - (logo_width_scaled/2), (height/4) - (logo_height_scaled/2), logo_width_scaled, logo_height_scaled };
    
    SDL_Rect start_button_rect = { (width/2) + (3 * button_font_size) - (int)(5.5 * button_font_size), (height/2) - 2 * button_font_size, 5 * button_font_size, button_font_size };
    SDL_Rect how_to_play_button_rect = { (width/2) - (int)(5.5 * button_font_size), (height/2) - button_font_size, 11* button_font_size, button_font_size };
    SDL_Rect resize_button_rect = { (width/2) + (int)(2.5 * button_font_size) - (int)(5.5 * button_font_size), (height/2), 6 * button_font_size, button_font_size };
    SDL_Rect exit_button_rect = { (width/2) + (int)(3.5 * button_font_size) - (int)(5.5 * button_font_size), (height/2) + button_font_size, 4 * button_font_size, button_font_size };
    
    SDL_Rect sand_button_rect = {   material_text_padding                                   , material_text_padding, 4 * material_button_font_size, material_button_font_size };
    SDL_Rect gravel_button_rect = { material_text_padding + material_button_font_size * 5   , material_text_padding, 6 * material_button_font_size, material_button_font_size };
    SDL_Rect water_button_rect = {  material_text_padding + material_button_font_size * 12  , material_text_padding, 5 * material_button_font_size, material_button_font_size };
    SDL_Rect oil_button_rect = {    material_text_padding + material_button_font_size * 18  , material_text_padding, 3 * material_button_font_size, material_button_font_size };
    SDL_Rect wall_button_rect = {   material_text_padding + material_button_font_size * 22  , material_text_padding, 4 * material_button_font_size, material_button_font_size };

    SDL_Rect music_button_rect = { width - padding + ((padding - play_pause_size) / 2), height - padding + ((padding - play_pause_size) / 2), play_pause_size, play_pause_size };
    
    SDL_Rect grid_button_rect = { 0, padding, width, height - (2 * padding) };

    SDL_Rect how_to_play_rect = { (width/2) - (how_to_play_width/2), (height/2) - (how_to_play_height/2), how_to_play_width, how_to_play_height };
    
    bool small = true;
    void change_screen_size();
};

#endif