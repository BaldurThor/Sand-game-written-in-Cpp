#include "materials.h"

Materials_struct* Materials_struct::sand = NULL;
Materials_struct* Materials_struct::gravel = NULL;
Materials_struct* Materials_struct::none = NULL;
Materials_struct* Materials_struct::water = NULL;
Materials_struct* Materials_struct::wall = NULL;

Materials_struct* Materials_struct::get_instance(Material material) {
    switch (material) {
        case SAND:
            if (sand == NULL) {
                sand = new Materials_struct();
                sand->noice = RNG::get_noice(BRUSH_SIZE, 0.5);
                sand->friction = 0.2;
                sand->velocity = 3;
                sand->color = { 255, 255, 0 };
                sand->liquid = false;
            }
            return sand;
        case GRAVEL:
            if (gravel == NULL) {
                gravel = new Materials_struct();
                gravel->noice = RNG::get_noice(BRUSH_SIZE, 0.9);
                gravel->friction = 0.8;
                gravel->velocity = 1;
                gravel->color = { 128, 128, 128 };
                gravel->liquid = false;
            }
            return gravel;
        case WATER:
            if (water == NULL) {
                water = new Materials_struct();
                water->noice = RNG::get_noice(BRUSH_SIZE, 1);
                water->friction = 0;
                water->velocity = 5;
                water->color = { 0, 0, 255 };
                water->liquid = true;
            }
            return water;
        case WALL:
            if (wall == NULL) {
                wall = new Materials_struct();
                wall->noice = RNG::get_noice(BRUSH_SIZE, 1);
                wall->friction = 1;
                wall->velocity = 0;
                wall->color = { 255, 255, 255 };
                wall->liquid = false;
            }
            return wall;
        case NONE:
            if (none == NULL) {
                none = new Materials_struct();
                none->noice = RNG::get_noice(BRUSH_SIZE, 1);
                none->friction = 0;
                none->velocity = 0;
                none->color = { 0, 0, 0 };
                none->liquid = false;
            }
            return none;
        default:
            return NULL;
    }
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
    if (noice != NULL) {
        delete noice;
    }
    if (water != NULL) {
        delete water;
    }
    if (wall != NULL) {
        delete wall;
    }
}