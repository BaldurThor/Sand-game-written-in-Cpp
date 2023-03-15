#ifndef MATERIALS_H
#define MATERIALS_H

#include "RNG.h"
#include "consts.h"

struct Color {
    int r;
    int g;
    int b;
};

struct Materials_struct
{
    static Materials_struct* sand;
    static Materials_struct* gravel;
    static Materials_struct* water;
    static Materials_struct* none;
    static Materials_struct* wall;
    bool* noice;
    bool liquid;
    double friction;
    int velocity;
    Color color;
    static Materials_struct* get_instance(Material);
    static void free_instance();
    ~Materials_struct();
};

#endif