#include "mediaHandler.h"

using namespace std;

MediaHandler::MediaHandler(SDL_Renderer *renderer, SDL_Window *window) {
    // Initialize SDL_mixer
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

    SDL_Surface *play_pause = IMG_Load(PLAY_PAUSE_PATH);
    if (play_pause == NULL) {
        throw runtime_error(string("Failed to load play/pause button! SDL_image Error: ") + IMG_GetError());
    }
    play_pause_texture = SDL_CreateTextureFromSurface(renderer, play_pause);
    if (play_pause_texture == NULL) {
        throw runtime_error(string("Failed to create texture from play/pause button! SDL Error: ") + SDL_GetError());
    }
    SDL_FreeSurface(play_pause);

    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
    Mix_PlayMusic(music, -1);
}

MediaHandler::~MediaHandler() {
    // Free the music.
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = NULL;

    // Free the sound effects.
    for (int i = 0; i < 6; i++) {
        Mix_FreeChunk(sounds[i]);
        sounds[i] = NULL;
    }

    // Free the logo texture.
    SDL_DestroyTexture(logo_texture);
    logo_texture = NULL;
    SDL_DestroyTexture(play_pause_texture);
    play_pause_texture = NULL;

    // Quit SDL_mixer.
    Mix_Quit();

    // Quit SDL_image.
    IMG_Quit();
}

void MediaHandler::play_sound(int sound) {
    Mix_PlayChannel(-1, sounds[sound], -1);
}

void MediaHandler::stop_sound() {
    Mix_HaltChannel(-1);
}

void MediaHandler::continue_music() {
    Mix_ResumeMusic();
    play_pause_state = false;
}

void MediaHandler::pause_music() {
    Mix_PauseMusic();
    play_pause_state = true;
}

SDL_Texture *MediaHandler::get_logo_texture() {
    return logo_texture;
}

SDL_Texture *MediaHandler::get_play_pause_texture() {
    return play_pause_texture;
}

SDL_Rect MediaHandler::get_play_pause_rect() {
    if (play_pause_state) {
        return {0, 0, PLAY_PAUSE_TEXTURE_SIZE, PLAY_PAUSE_TEXTURE_SIZE};
    } else {
        return {PLAY_PAUSE_TEXTURE_SIZE, 0, PLAY_PAUSE_TEXTURE_SIZE*2, PLAY_PAUSE_TEXTURE_SIZE};
    }
}