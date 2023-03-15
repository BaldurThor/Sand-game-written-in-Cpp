#ifndef MATERIALS_H
#define MATERIALS_H

#include "consts.h"
#include <string>

using namespace std;

enum Material {
    NONE,
    SAND,
    GRAVEL,
    STONE
};

struct materials
{
    string name;
    Material material;
    double density;
    double friction;
    int velocity;
};

#endif