#ifndef SAND_MEDIA_HANDLER_H
#define SAND_MEDIA_HANDLER_H

#include <stdexcept>
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "../consts.h"

class MediaHandler {
    private:
        Mix_Music *music;
        Mix_Chunk *sounds[6];
        SDL_Texture *logo_texture;
        SDL_Texture *play_pause_texture;
        bool play_pause_state = false;
    public:
        MediaHandler(SDL_Renderer *, SDL_Window *);
        ~MediaHandler();
        void play_sound(int);
        void stop_sound();
        void continue_music();
        void pause_music();
        SDL_Texture *get_logo_texture();
        SDL_Texture *get_play_pause_texture();
        SDL_Rect get_play_pause_rect();
};

#endif