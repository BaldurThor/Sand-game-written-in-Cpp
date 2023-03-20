#include "renderer.h"

void Renderer::reset_grid() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            grid[i][j] = { NONE };
        }
    }
}

void Renderer::put_pixle(int x, int y, Material state) {
    if (x < SCREEN_WIDTH && y < SCREEN_HEIGHT - (2 * SCREEN_PADDING) && x >= 0 && y >= 0) {
        if (grid[x / GRID_CELL_SIZE][y / GRID_CELL_SIZE].material == NONE || state == NONE || state == WALL) {
            grid[x / GRID_CELL_SIZE][y / GRID_CELL_SIZE].material = state;
            grid[x / GRID_CELL_SIZE][y / GRID_CELL_SIZE].velocity = Materials_struct::get_instance(state)->weight;
            grid[x / GRID_CELL_SIZE][y / GRID_CELL_SIZE].color_noise = RNG::get_color_noise();
        }
    }
}


void Renderer::put_line(int x, int y, int dx, int dy, Material state) {
    if (x != dx && y != dy) {
        throw std::invalid_argument("put_line only supports horizontal and vertical lines");
    }
    if (x == dx) {
        if (y > dy) {
            int place = y;
            y = dy;
            dy = place;
        }
        for (int i = y; i <= dy; i++) {
            put_pixle(x, i, state);
        }
    }
    else {
        if (x > dx) {
            int place = x;
            x = dx;
            dx = place;
        }
        for (int i = x; i <= dx; i++) {
            put_pixle(i, y, state);
        }
    }
}


void Renderer::draw_circle(int x, int y, int dx, int dy, Material state) {
    put_line(x+dx, y+dy, x-dx, y+dy, state);
    put_line(x+dy, y+dx, x-dy, y+dx, state);
    put_line(x+dx, y-dy, x-dx, y-dy, state);
    put_line(x+dy, y-dx, x-dy, y-dx, state);
}

void Renderer::bresenham_algo(int x, int y, Material state) {
    int radius = brush_size/2, dx = 0, dy = radius;
    int decesionParameter = 3 - 2 * radius;
    draw_circle(x, y, dx, dy, state);
    while (dy >= dx) {
        dx++;
        if (decesionParameter > 0) {
            dy--;
            decesionParameter = decesionParameter + 4 * (dx - dy) + 10;
        }
        else {
            decesionParameter = decesionParameter + 4 * dx + 6;
        }
        draw_circle(x, y, dx, dy, state);
    }
}

void Renderer::fill_grid(int x, int y, int dx, int dy, Material state) {

    int fx = abs(dx - x);
    int fy = abs(dy - y);
    int sx = x < dx ? 1 : -1;
    int sy = y < dy ? 1 : -1;
    int err = fx - fy;

    while (true) {
        bresenham_algo(x, y, state);
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