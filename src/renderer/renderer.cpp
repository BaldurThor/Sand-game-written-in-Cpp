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
    sand_sound = Mix_LoadWAV(SAND_SOUND_PATH);
    gravel_sound = Mix_LoadWAV(GRAVEL_SOUND_PATH);
    water_sound = Mix_LoadWAV(WATER_SOUND_PATH);
    oil_sound = Mix_LoadWAV(OIL_SOUND_PATH);
    wall_sound = Mix_LoadWAV(WALL_SOUND_PATH);
    remove_sound = Mix_LoadWAV(REMOVE_SOUND_PATH);
    if (sand_sound == NULL) {
        throw runtime_error(string("Failed to load sand sound effect! SDL_mixer Error: ") + Mix_GetError());
    }
    if (gravel_sound == NULL) {
        throw runtime_error(string("Failed to load sand sound effect! SDL_mixer Error: ") + Mix_GetError());
    }
    if (water_sound == NULL) {
        throw runtime_error(string("Failed to load sand sound effect! SDL_mixer Error: ") + Mix_GetError());
    }
    if (oil_sound == NULL) {
        throw runtime_error(string("Failed to load sand sound effect! SDL_mixer Error: ") + Mix_GetError());
    }
    if (wall_sound == NULL) {
        throw runtime_error(string("Failed to load sand sound effect! SDL_mixer Error: ") + Mix_GetError());
    }
    if (remove_sound == NULL) {
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


    SDL_ShowCursor(SDL_DISABLE);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    Mix_FreeChunk(sand_sound);
    Mix_FreeChunk(gravel_sound);
    Mix_FreeChunk(water_sound);
    Mix_FreeChunk(oil_sound);
    Mix_FreeChunk(wall_sound);
    Mix_FreeChunk(remove_sound);
    sand_sound = NULL;
    gravel_sound = NULL;
    water_sound = NULL;
    oil_sound = NULL;
    wall_sound = NULL;
    remove_sound = NULL;
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
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    RNG::free_instance();
    Materials_struct::free_instance();
}