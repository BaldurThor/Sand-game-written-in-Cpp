#include <iostream>
#include "SDL2/SDL.h"
#include "RNG.h"
#include "materials.h"
#include "consts.h"

using namespace std;

Material grid[GRID_WIDTH][GRID_HEIGHT] = { NONE };

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
}

void update() {

    int velocity = 1;

    for (int height = GRID_HEIGHT - 1; height >= 0; height--) {
        for (int width = 0; width < GRID_WIDTH; width++) {
            if (grid[width][height] == SAND) {
                if (height == GRID_HEIGHT - 1) {
                    cout << "Sand at bottom" << endl;
                    continue;
                }
                if (grid[width][height + 1] == NONE) {
                    grid[width + velocity][height + 1] = SAND;
                    grid[width][height] = NONE;
                } else if (grid[width + 1][height + 1] == NONE) {
                    grid[width + 1][height + 1] = SAND;
                    grid[width][height] = NONE;
                } else if (grid[width - 1][height + 1] == NONE) {
                    grid[width - 1][height + 1] = SAND;
                    grid[width][height] = NONE;
                }


            }
        }
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int height = 0; height < GRID_HEIGHT; height++) {
        for (int width = 0; width < GRID_WIDTH; width++) {
            if (grid[width][height] == SAND) {
                SDL_Rect fillRect = {width * GRID_CELL_SIZE, height * GRID_CELL_SIZE, GRID_CELL_SIZE, GRID_CELL_SIZE};
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
                SDL_RenderFillRect(renderer, &fillRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void fill(int x, int y, Material state) {
    int brush_size = BRUSH_SIZE / 2;
    bool* noice = RNG::get_noice(BRUSH_SIZE, 0.0);
    for (int xi = x - brush_size; xi < x + brush_size; xi++) {
        for (int yi = y - brush_size; yi < y + brush_size; yi++) {
            if (xi < SCREEN_WIDTH && yi < SCREEN_HEIGHT && xi >= 0 && yi >= 0) {
                cout << xi << " " << yi << endl;
                grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE] = state;
            }
        }
    }
    delete noice;
    
}

int main(int argc, char* argv[])
{
    if (!init()) {
        cout << "Failed to initialize!" << endl;
    } else {
        Uint64 ticksA = 0, ticksB = 0, ticksDelta;
        bool quit = false;
        SDL_Event e;
        int x, y;

        while (!quit) {
            ticksA = SDL_GetTicks();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } 
                /*else if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    grid[x / GRID_CELL_SIZE][y / GRID_CELL_SIZE] = SAND;
                }*/
            }
            if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                if (x < SCREEN_WIDTH && y < SCREEN_HEIGHT && x >= 0 && y >= 0) {
                    fill(x, y, SAND);
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

    close();
    return 0;
}
