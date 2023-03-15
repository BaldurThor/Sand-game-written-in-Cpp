#include <iostream>
#include "SDL2/SDL.h"

int grid() {
    int grid_cell_size = 36;
    int grid_width = 29;
    int grid_height = 23;

    SDL_Rect grid_cursor;

    grid_cursor.x = (grid_width - 1) / 2 * grid_cell_size;
    grid_cursor.y = (grid_height - 1) / 2 * grid_cell_size;
    grid_cursor.w = grid_cell_size;
    grid_cursor.h = grid_cell_size;

    SDL_Rect grid_cursor_ghost = {grid_cursor.x, grid_cursor.y, grid_cursor.w, grid_cursor.h};

    // Dark theme.
    SDL_Color grid_background = {22, 22, 22, 255}; // Barely Black
    SDL_Color grid_line_color = {44, 44, 44, 255}; // Dark grey
    SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
    SDL_Color grid_cursor_color = {255, 255, 255, 255}; // White
    return 1;
}