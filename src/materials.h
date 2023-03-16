#ifndef MATERIALS_H
#define MATERIALS_H

#include "RNG.h"
#include "consts.h"

struct Pixle {
    Material material = NONE;
    double velocity = 0; // used for weight calculations
    Color color = {0,0,0}; // for noice
    bool operator==(const Pixle& other) const {
        return material == other.material;
    }
    bool operator!=(const Pixle& other) const {
        return !(*this == other);
    }
    bool operator==(const Material& other) const {
        return material == other;
    }
    bool operator!=(const Material& other) const {
        return !(*this == other);
    }
};

struct Materials_struct
{
    static Materials_struct* sand;
    static Materials_struct* gravel;
    static Materials_struct* water;
    static Materials_struct* none;
    static Materials_struct* wall;
    bool* noise;
    bool liquid;
    bool immovable;
    double friction;
    int velocity;
    int weight;
    Color color;
    static Materials_struct* get_instance(Pixle);
    static Materials_struct* get_instance(Material);
    static void free_instance();
    ~Materials_struct();
};

#endif