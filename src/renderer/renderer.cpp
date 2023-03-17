#include "renderer.h"

using namespace std;

Renderer::Renderer() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw runtime_error(string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
    }
    window = SDL_CreateWindow("Sand Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        throw runtime_error(string("Window could not be created! SDL_Error: ") + SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        throw runtime_error(string("Renderer could not be created! SDL Error: ") + SDL_GetError());
    }
    
    if (TTF_Init() < 0) {
        throw runtime_error(string("SDL_ttf could not initialize! SDL_ttf Error: ") + SDL_GetError());
    }
    SDL_ShowCursor(SDL_DISABLE);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    TTF_Quit();
    SDL_Quit();
    RNG::free_instance();
    Materials_struct::free_instance();
}