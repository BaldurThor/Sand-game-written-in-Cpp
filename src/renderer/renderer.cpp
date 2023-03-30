#include "renderer.h"

using namespace std;

Renderer::Renderer() {
    screen = new Screen();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw runtime_error(string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
    }
    window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen->width, screen->height, 0);

    if (window == NULL) {
        throw runtime_error(string("Window could not be created! SDL_Error: ") + SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        throw runtime_error(string("Renderer could not be created! SDL Error: ") + SDL_GetError());
    }

    mediaHandler = new MediaHandler(renderer, window);

    // Initialize SDL_ttf.
    if (TTF_Init() < 0) {
        throw runtime_error(string("SDL_ttf could not initialize! SDL_ttf Error: ") + SDL_GetError());
    }

    if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ) {
        throw runtime_error(string("SDL_image could not initialize! SDL_image Error: ") + IMG_GetError());
    }

    start_button = new Button(screen->start_button_rect, MENU_BUTTON_COLOR, MENU_BUTTON_HOVER_COLOR);
    how_to_play_button = new Button(screen->how_to_play_button_rect, MENU_BUTTON_COLOR, MENU_BUTTON_HOVER_COLOR);
    exit_button = new Button(screen->exit_button_rect, MENU_BUTTON_COLOR, MENU_BUTTON_HOVER_COLOR);
    sand_button = new Button(screen->sand_button_rect, TEXT_COLOR, TEXT_HOVER_COLOR);
    gravel_button = new Button(screen->gravel_button_rect, TEXT_COLOR, TEXT_HOVER_COLOR);
    water_button = new Button(screen->water_button_rect, TEXT_COLOR, TEXT_HOVER_COLOR);
    oil_button = new Button(screen->oil_button_rect, TEXT_COLOR, TEXT_HOVER_COLOR);
    wall_button = new Button(screen->wall_button_rect, TEXT_COLOR, TEXT_HOVER_COLOR);
    music_button = new Button(screen->music_button_rect, TEXT_COLOR, TEXT_HOVER_COLOR);
    grid_button = new Button(screen->grid_button_rect, TEXT_COLOR, TEXT_HOVER_COLOR);

    SDL_ShowCursor(SDL_DISABLE);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    delete(screen);
    delete(start_button);
    delete(how_to_play_button);
    delete(exit_button);
    delete(sand_button);
    delete(gravel_button);
    delete(water_button);
    delete(oil_button);
    delete(wall_button);
    delete(music_button);
    delete(grid_button);
    delete(mediaHandler);
    TTF_Quit();
    SDL_Quit();
    RNG::free_instance();
    Materials_struct::free_instance();
}