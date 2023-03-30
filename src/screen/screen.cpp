#include "screen.h"

void Screen::change_screen_size() {
    double modifier = 0.5;
    logo_scale = LOGO_SCALE;
    if (small) {
        modifier = 2.0;
        logo_scale = 2.5;
    }
    width = width * modifier;
    height = height * modifier;
    padding = padding * modifier;
    grid_cell_size = grid_cell_size * modifier;
    play_pause_size = play_pause_size * modifier;

    logo_width_scaled = LOGO_WIDTH * logo_scale;
    logo_height_scaled = LOGO_HEIGHT * logo_scale;

    text_padding = text_padding * modifier;
    button_font_size = button_font_size * modifier;
    material_text_padding = material_text_padding * modifier;
    material_button_font_size = material_button_font_size * modifier;
    how_to_play_font_size = how_to_play_font_size * modifier;
    how_to_play_width = 64 * how_to_play_font_size;
    how_to_play_height = 16 * how_to_play_font_size;

    logo_rect = { (width/2) - (logo_width_scaled/2), (height/4) - (logo_height_scaled/2), logo_width_scaled, logo_height_scaled };
    
    start_button_rect = { (width/2) + (3 * button_font_size) - (int)(5.5 * button_font_size), (height/2) - 2 * button_font_size, 5 * button_font_size, button_font_size };
    how_to_play_button_rect = { (width/2) - (int)(5.5 * button_font_size), (height/2) - button_font_size, 11* button_font_size, button_font_size };
    exit_button_rect = { (width/2) + (int)(3.5 * button_font_size) - (int)(5.5 * button_font_size), (height/2), 4 * button_font_size, button_font_size };
    
    sand_button_rect = {   material_text_padding                                   , material_text_padding, 4 * material_button_font_size, material_button_font_size };
    gravel_button_rect = { material_text_padding + material_button_font_size * 5   , material_text_padding, 6 * material_button_font_size, material_button_font_size };
    water_button_rect = {  material_text_padding + material_button_font_size * 12  , material_text_padding, 5 * material_button_font_size, material_button_font_size };
    oil_button_rect = {    material_text_padding + material_button_font_size * 18  , material_text_padding, 3 * material_button_font_size, material_button_font_size };
    wall_button_rect = {   material_text_padding + material_button_font_size * 22  , material_text_padding, 4 * material_button_font_size, material_button_font_size };

    music_button_rect = { width - padding + ((padding - play_pause_size) / 2), height - padding + ((padding - play_pause_size) / 2), play_pause_size, play_pause_size };
    
    grid_button_rect = { 0, padding, width, height - (2 * padding) };

    how_to_play_rect = { (width/2) - (how_to_play_width/2), (height/2) - (how_to_play_height/2), how_to_play_width, how_to_play_height };

    small = !small;
}