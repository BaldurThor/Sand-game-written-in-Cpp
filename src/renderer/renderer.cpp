#include "renderer.h"

using namespace std;

Renderer::Renderer() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw runtime_error(string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
    }
    window = SDL_CreateWindow("Sand Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (window == NULL) {
        throw runtime_error(string("Window could not be created! SDL_Error: ") + SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        throw runtime_error(string("Renderer could not be created! SDL Error: ") + SDL_GetError());
    }

    // Initialize SDL_mixer.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw runtime_error(string("SDL_mixer could not initialize! SDL_mixer Error: ") + Mix_GetError());
    }

    // Load music.
    music = Mix_LoadMUS(MUSIC_PATH);
    if (music == NULL) {
        throw runtime_error(string("Failed to load music! SDL_mixer Error: ") + Mix_GetError());
    }
    // Load sound effects.
    sounds[0] = Mix_LoadWAV(REMOVE_SOUND_PATH);
    sounds[1] = Mix_LoadWAV(SAND_SOUND_PATH);
    sounds[2] = Mix_LoadWAV(GRAVEL_SOUND_PATH);
    sounds[3] = Mix_LoadWAV(WATER_SOUND_PATH);
    sounds[4] = Mix_LoadWAV(OIL_SOUND_PATH);
    sounds[5] = Mix_LoadWAV(WALL_SOUND_PATH);
    
    if (sounds[0] == NULL) {
        throw runtime_error(string("Failed to load sand sound effect! SDL_mixer Error: ") + Mix_GetError());
    }
    if (sounds[1] == NULL) {
        throw runtime_error(string("Failed to load sand sound effect! SDL_mixer Error: ") + Mix_GetError());
    }
    if (sounds[2] == NULL) {
        throw runtime_error(string("Failed to load sand sound effect! SDL_mixer Error: ") + Mix_GetError());
    }
    if (sounds[3] == NULL) {
        throw runtime_error(string("Failed to load sand sound effect! SDL_mixer Error: ") + Mix_GetError());
    }
    if (sounds[4] == NULL) {
        throw runtime_error(string("Failed to load sand sound effect! SDL_mixer Error: ") + Mix_GetError());
    }
    if (sounds[5] == NULL) {
        throw runtime_error(string("Failed to load sand sound effect! SDL_mixer Error: ") + Mix_GetError());
    }
    
    Mix_PlayMusic(music, -1);

    // Initialize SDL_ttf.
    if (TTF_Init() < 0) {
        throw runtime_error(string("SDL_ttf could not initialize! SDL_ttf Error: ") + SDL_GetError());
    }

    if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ) {
        throw runtime_error(string("SDL_image could not initialize! SDL_image Error: ") + IMG_GetError());
    }

    SDL_Surface *logo = IMG_Load(LOGO_PATH);
    if (logo == NULL) {
        throw runtime_error(string("Failed to load logo! SDL_image Error: ") + IMG_GetError());
    }
    logo_texture = SDL_CreateTextureFromSurface(renderer, logo);
    if (logo_texture == NULL) {
        throw runtime_error(string("Failed to create texture from logo! SDL Error: ") + SDL_GetError());
    }
    SDL_FreeSurface(logo);

    SDL_Surface *icon = IMG_Load(ICON_PATH);
    if (icon == NULL) {
        throw runtime_error(string("Failed to load icon! SDL_image Error: ") + IMG_GetError());
    }
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    start_button = new Button(START_BUTTON_RECT, MENU_BUTTON_COLOR, MENU_BUTTON_HOVER_COLOR);
    how_to_play_button = new Button(HOW_TO_PLAY_BUTTON_RECT, MENU_BUTTON_COLOR, MENU_BUTTON_HOVER_COLOR);
    exit_button = new Button(EXIT_BUTTON_RECT, MENU_BUTTON_COLOR, MENU_BUTTON_HOVER_COLOR);
    sand_button = new Button(SAND_BUTTON_RECT, TEXT_COLOR, TEXT_HOVER_COLOR);
    gravel_button = new Button(GRAVEL_BUTTON_RECT, TEXT_COLOR, TEXT_HOVER_COLOR);
    water_button = new Button(WATER_BUTTON_RECT, TEXT_COLOR, TEXT_HOVER_COLOR);
    oil_button = new Button(OIL_BUTTON_RECT, TEXT_COLOR, TEXT_HOVER_COLOR);
    wall_button = new Button(WALL_BUTTON_RECT, TEXT_COLOR, TEXT_HOVER_COLOR);
    music_button = new Button(MUSIC_BUTTON_RECT, TEXT_COLOR, TEXT_HOVER_COLOR);
    grid_button = new Button(GRID_BUTTON_RECT, TEXT_COLOR, TEXT_HOVER_COLOR);

    SDL_ShowCursor(SDL_DISABLE);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    Mix_FreeChunk(sounds[0]);
    Mix_FreeChunk(sounds[1]);
    Mix_FreeChunk(sounds[2]);
    Mix_FreeChunk(sounds[3]);
    Mix_FreeChunk(sounds[4]);
    Mix_FreeChunk(sounds[5]);
    music = NULL;
    window = NULL;
    renderer = NULL;
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
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    RNG::free_instance();
    Materials_struct::free_instance();
}