#ifndef SAND_COLOR_MIXER_H
#define SAND_COLOR_MIXER_H

#include <SDL2/SDL.h>
#include "../RNG/RNG.h"
#include "colorNoise.h"

SDL_Color mix_colors(SDL_Color color1, SDL_Color color2);
SDL_Color add_noise(SDL_Color color, ColorNoise noise);

#endif