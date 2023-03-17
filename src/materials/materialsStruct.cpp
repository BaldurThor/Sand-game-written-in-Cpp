#include "materialsStruct.h"

Materials_struct* Materials_struct::sand = NULL;
Materials_struct* Materials_struct::gravel = NULL;
Materials_struct* Materials_struct::none = NULL;
Materials_struct* Materials_struct::water = NULL;
Materials_struct* Materials_struct::wall = NULL;
Materials_struct* Materials_struct::oil = NULL;

Materials_struct* Materials_struct::get_instance(Material material) {
    switch (material) {
        case SAND:
            if (sand == NULL) {
                sand = new Materials_struct();
                sand->friction = 0.2;
                sand->velocity = 3;
                sand->color = { 167, 123, 91 };
                sand->weight = 4;
            }
            return sand;
        case GRAVEL:
            if (gravel == NULL) {
                gravel = new Materials_struct();
                gravel->friction = 0.8;
                gravel->velocity = 2;
                gravel->color = { 134, 129, 136 };
                gravel->weight = 6;
            }
            return gravel;
        case WATER:
            if (water == NULL) {
                water = new Materials_struct();
                water->friction = 0.1;
                water->velocity = 10;
                water->color = { 75, 128, 202 };
                water->liquid = true;
                water->weight = 2;
            }
            return water;
        case OIL:
            if (oil == NULL) {
                oil = new Materials_struct();
                oil->friction = 0.2;
                oil->velocity = 5;
                oil->color = { 0, 0, 0 };
                oil->liquid = true;
                oil->weight = 1;
            }
            return oil;
        case WALL:
            if (wall == NULL) {
                wall = new Materials_struct();
                wall->friction = 1;
                wall->velocity = 0;
                wall->color = { 69, 68, 79 };
                wall->immovable = true;
                wall->weight = __INT_MAX__;
            }
            return wall;
        case NONE:
            if (none == NULL) {
                none = new Materials_struct();
                none->friction = 0;
                none->velocity = 0;
                none->color = { 0, 0, 0 };
                none->immovable = true;
                none->weight = 0;
            }
            return none;
        default:
            return NULL;
    }
}

Materials_struct* Materials_struct::get_instance(Pixle pixle) {
    return get_instance(pixle.material);
}

void Materials_struct::free_instance() {
    if (sand != NULL) {
        delete sand;
        sand = NULL;
    }
    if (gravel != NULL) {
        delete gravel;
        gravel = NULL;
    }
    if (none != NULL) {
        delete none;
        none = NULL;
    }
    if (water != NULL) {
        delete water;
        water = NULL;
    }
    if (wall != NULL) {
        delete wall;
        wall = NULL;
    }
    if (oil != NULL) {
        delete oil;
        oil = NULL;
    }

}

Materials_struct::~Materials_struct() {
    if (sand != NULL) {
        delete sand;
    }
    if (gravel != NULL) {
        delete gravel;
    }
    if (none != NULL) {
        delete none;
    }
    if (water != NULL) {
        delete water;
    }
    if (wall != NULL) {
        delete wall;
    }
    if (oil != NULL) {
        delete oil;
    }
}