#include "colorMixer.h"

SDL_Color mix_colors(SDL_Color color1, SDL_Color color2) {
    SDL_Color color;
    short c = color1.r + color2.r / 2;
    color.r = c;
    c = color1.g + color2.g / 2;
    color.g = c;
    c = color1.b + color2.b / 2;
    color.b = c;
    return color;
}

SDL_Color add_noise(SDL_Color color, ColorNoise noise) {
    SDL_Color color2;
    short c = color.r + noise.r;
    color2.r = c < 0 ? 0 : c > 255 ? 255 : c;
    c = color.g + noise.g;
    color2.g = c < 0 ? 0 : c > 255 ? 255 : c;
    c = color.b + noise.b;
    color2.b = c < 0 ? 0 : c > 255 ? 255 : c;
    return color2;
}