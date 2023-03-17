#include "renderer.h"

void Renderer::reset_grid() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            grid[i][j] = { NONE };
        }
    }
}

void Renderer::draw_circle(int xc, int yc, int x, int y, Material state) {
    int brush_rad = brush_size / 2;
    for (int xi = xc - brush_rad; xi < xc + brush_rad; xi++) {
            for (int yi = yc - brush_rad; yi < yc + brush_rad; yi++) {
                if (xi < SCREEN_WIDTH && yi < SCREEN_HEIGHT - (2 * SCREEN_PADDING) && xi >= 0 && yi >= 0) {
                    if (grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].material == NONE || state == NONE || state == WALL) {
                        grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].material = state;
                        grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].velocity = Materials_struct::get_instance(state)->weight;
                        grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].color_noise = RNG::get_color_noise();
                    }
                }
            }
        }
}

void Renderer::bresenham_algo(int xc, int yc, int r, Material state) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    draw_circle(xc, yc, x, y, state);
    while (x <= y) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else {
            d = d + 4 * x + 6;
        }
        draw_circle(xc, yc, x, y, state);
    }
}

void Renderer::fill_grid(int xa, int ya, int xb, int yb, Material state) {
    int dx = abs(xa - xb), dy = abs(ya - yb);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
    int x, y, xEnd;
    int brush_rad = brush_size / 2;
    if (xa > xb) {
        x = xb;
        y = yb;
        xEnd = xa;
    }
    else {
        x = xa;
        y = ya;
        xEnd = xb;
    }
    bresenham_algo(x, y, brush_rad, state);
    while (x < xEnd) {
        x++;
        if (p < 0) {
            p += twoDy;
        }
        else {
            y++;
            p += twoDyMinusDx;
        }
        bresenham_algo(x, y, brush_rad, state);
    }
}