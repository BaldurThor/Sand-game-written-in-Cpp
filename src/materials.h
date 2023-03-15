#ifndef MATERIALS_H
#define MATERIALS_H

#include "RNG.h"

enum Material {
    NONE,
    SAND,
    GRAVEL,
    WATER
};

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
    bool* noice;
    bool liquid;
    bool direction;
    int cell_size;
    int brush_size;
    double friction;
    int velocity;
    Color color;
    static Materials_struct* get_instance(Material);
    static void free_instance();
    ~Materials_struct();
};

#endif