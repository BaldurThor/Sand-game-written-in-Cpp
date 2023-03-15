#include <iostream>
#include "SDL2/SDL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int GRID_CELL_SIZE = 10;
const int GRID_WIDTH = SCREEN_WIDTH / GRID_CELL_SIZE;
const int GRID_HEIGHT = SCREEN_HEIGHT / GRID_CELL_SIZE;

using namespace std;

enum CellState {
    NONE,
    SAND
};

CellState grid[GRID_WIDTH][GRID_HEIGHT] = { NONE };

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
    for (int height = GRID_HEIGHT - 1; height >= 0; height--) {
        for (int width = 0; width < GRID_WIDTH; width++) {
            if (grid[width][height] == SAND) {
                if (height == GRID_HEIGHT - 1) {
                    continue;
                }
                if (grid[width][height + 1] == NONE) {
                    grid[width][height + 1] = SAND;
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

int main(int argc, char* argv[])
{
    if (!init()) {
        cout << "Failed to initialize!" << endl;
    } else {
        bool quit = false;
        SDL_Event e;

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    grid[x / GRID_CELL_SIZE][y / GRID_CELL_SIZE] = SAND;
                }
            }

            update();
            render();
        }
    }

    close();
    return 0;
}
