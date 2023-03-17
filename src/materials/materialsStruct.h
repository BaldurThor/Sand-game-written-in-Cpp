#ifndef SAND_MATERIALS_STRUCT_H
#define SAND_MATERIALS_STRUCT_H

#include "SDL2/SDL.h"

#include "../RNG/RNG.h"
#include "pixle.h"

struct Materials_struct
{
    static Materials_struct* sand;
    static Materials_struct* gravel;
    static Materials_struct* water;
    static Materials_struct* none;
    static Materials_struct* wall;
    static Materials_struct* oil;
    bool liquid = false;
    bool immovable = false;
    double friction;
    int velocity;
    int weight;
    SDL_Color color;
    static Materials_struct* get_instance(Pixle);
    static Materials_struct* get_instance(Material);
    static void free_instance();
    ~Materials_struct();
};

#endif