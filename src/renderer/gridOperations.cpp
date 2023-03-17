#include "renderer.h"

void Renderer::reset_grid() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            grid[i][j] = { NONE };
        }
    }
}

void Renderer::fill_grid(int x, int y, int dx, int dy, Material state) {

    int fx = abs(dx - x);
    int fy = abs(dy - y);
    int sx = x < dx ? 1 : -1;
    int sy = y < dy ? 1 : -1;
    int err = fx - fy;

    int brush_rad = brush_size / 2;

    while (true) {
        for (int xi = x - brush_rad; xi < x + brush_rad; xi++) {
            for (int yi = y - brush_rad; yi < y + brush_rad; yi++) {
                if (xi < SCREEN_WIDTH && yi < SCREEN_HEIGHT - (2 * SCREEN_PADDING) && xi >= 0 && yi >= 0) {
                    if (grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].material == NONE || state == NONE || state == WALL) {
                        grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].material = state;
                        grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].velocity = Materials_struct::get_instance(state)->weight;
                        grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].color_noise = RNG::get_color_noise();
                    }
                }
            }
        }
        if (x == dx && y == dy) {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -fy) {
            err -= fy;
            x += sx;
        }
        if (e2 < fx) {
            err += fx;
            y += sy;
        }
    }
}