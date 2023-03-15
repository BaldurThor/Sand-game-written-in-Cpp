#include <iostream>
#include "SDL2/SDL.h"
#include "RNG.h"
#include "materials.h"
#include "consts.h"

using namespace std;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    window = SDL_CreateWindow("Sand Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
    RNG::free_instance();
    Materials_struct::free_instance();
}

bool left_update(int width, int height, Material mat) {
    Materials_struct* mat_struct = Materials_struct::get_instance(mat);
    int height_mod = 1;

    if (mat_struct->liquid) {
        height_mod = 0;
    }
    else if (height == GRID_HEIGHT - 1) {
        return false;
    }

    int velocity = RNG::get_int(1, mat_struct->velocity);
        if (width - velocity < 0) {
            return false;
        }
    if (grid[width - velocity][height + height_mod] == NONE) {
        grid[width - velocity][height + height_mod] = mat;
        grid[width][height] = NONE;
        return true;
    }
    return false;
}

bool right_update(int width, int height, Material mat) {
    Materials_struct* mat_struct = Materials_struct::get_instance(mat);
    int height_mod = 1;

    if (mat_struct->liquid) {
        height_mod = 0;
    }
    else if (height == GRID_HEIGHT - 1) {
        return false;
    }
    
    int velocity = RNG::get_int(1, mat_struct->velocity);
        if (width + velocity > GRID_WIDTH - 1) {
            return false;
        }
    if (grid[width + velocity][height + height_mod] == NONE) {
        grid[width + velocity][height + height_mod] = mat;
        grid[width][height] = NONE;
        return true;
    } 
    return false;
}

void update() {
    for (int height = GRID_HEIGHT - 1; height >= 0; height--) {
        for (int width = 0; width < GRID_WIDTH; width++) {
            if (grid[width][height] != NONE) {
                Material mat = grid[width][height], mat_place;
                if (height != GRID_HEIGHT - 1 && (grid[width][height + 1] == NONE || (mat != WATER && grid[width][height + 1] == WATER))) {
                    mat_place = grid[width][height + 1];
                    grid[width][height + 1] = mat;
                    grid[width][height] = mat_place;
                }
                else if (RNG::get_bool(Materials_struct::get_instance(mat)->friction)){
                    if (RNG::get_bool()) {
                        if (!left_update(width, height, mat)) {
                            right_update(width, height, mat);
                        }
                    }
                    else {
                        if (!right_update(width, height, mat)) {
                            left_update(width, height, mat);
                        }
                    }
                }
            }
        }
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    Materials_struct* mat;
    for (int height = 0; height < GRID_HEIGHT; height++) {
        for (int width = 0; width < GRID_WIDTH; width++) {
            if (grid[width][height] != NONE) {
                mat = Materials_struct::get_instance(grid[width][height]);
                SDL_Rect fillRect = {width * GRID_CELL_SIZE, height * GRID_CELL_SIZE, GRID_CELL_SIZE, GRID_CELL_SIZE};
                SDL_SetRenderDrawColor(renderer, mat->color.r, mat->color.g, mat->color.b, 0xFF);
                SDL_RenderFillRect(renderer, &fillRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void fill(int x, int y, Material state) {
    int brush_size = BRUSH_SIZE / 2;
    for (int xi = x - brush_size; xi < x + brush_size; xi++) {
        for (int yi = y - brush_size; yi < y + brush_size; yi++) {
            if (xi < SCREEN_WIDTH && yi < SCREEN_HEIGHT && xi >= 0 && yi >= 0) {
                grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE] = state;
            }
        }
    }
}

void run() {
    Uint64 ticksA = 0, ticksB = 0, ticksDelta;
    bool quit = false, mousePressed = false;
    SDL_Event e;
    Material mat = SAND;
    int x, y;

    while (!quit) {
        ticksA = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mousePressed = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mousePressed = false;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_1:
                            mat = SAND;
                            break;
                        case SDLK_2:
                            mat = GRAVEL;
                            break;
                        case SDLK_3:
                            mat = WATER;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        if (mousePressed) {
            if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                fill(x, y, mat);
            }
            else {
                fill(x, y, NONE);
            }
        }
        ticksDelta = ticksA - ticksB;
        if (ticksDelta > TICK_RATE) {
            ticksB = ticksA;
            update();
            render();
        }
    }
}

int main(int argc, char* argv[])
{
    if (!init()) {
        cout << "Failed to initialize!" << endl;
    }
    else {
        run();
    }
    close();
    return 0;
}
