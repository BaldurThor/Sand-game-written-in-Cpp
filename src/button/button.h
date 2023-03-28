#ifndef SAND_BUTTON_H
#define SAND_BUTTON_H

#include "SDL2/SDL.h"

class Button {
    public:
        Button(SDL_Rect, SDL_Color, SDL_Color);
        void update(int, int);
        SDL_Color get_color();
        bool within(int, int);
    private:
        SDL_Rect rect;
        SDL_Color current_color;
        SDL_Color default_color;
        SDL_Color hover_color;
};

#endif