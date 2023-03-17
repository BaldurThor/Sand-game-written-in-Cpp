#ifndef SAND_PIXLE_H
#define SAND_PIXLE_H

#include "material.h"
#include "../color/colorNoise.h"

struct Pixle {
    Material material = NONE;
    double velocity = 0; // used for weight calculations
    ColorNoise color_noise = {0, 0, 0};
    bool operator==(const Pixle& other) const;
    bool operator!=(const Pixle& other) const;
    bool operator==(const Material& other) const;
    bool operator!=(const Material& other) const;
};

#endif