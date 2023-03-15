#ifndef MATERIALS_H
#define MATERIALS_H

#include "RNG.h"

enum Material {
    NONE,
    SAND,
    GRAVEL
};

struct Color {
    int r;
    int g;
    int b;
};

struct Materials_struct
{
    bool* noice;
    int cell_size;
    int brush_size;
    double friction;
    int velocity;
    Color color;
    Materials_struct(Material);
    ~Materials_struct();
};

#endif