#include "materials.h"

Materials_struct* Materials_struct::sand = NULL;
Materials_struct* Materials_struct::gravel = NULL;
Materials_struct* Materials_struct::none = NULL;
Materials_struct* Materials_struct::water = NULL;

Materials_struct* Materials_struct::get_instance(Material material) {
    switch (material) {
        case SAND:
            if (sand == NULL) {
                sand = new Materials_struct();
                sand->noice = RNG::get_noice(sand->brush_size, 0.5);
                sand->cell_size = 2;
                sand->brush_size = 5;
                sand->friction = 0.2;
                sand->velocity = 3;
                sand->color = { 255, 255, 0 };
                sand->liquid = false;
                sand->direction = false;
            }
            return sand;
        case GRAVEL:
            if (gravel == NULL) {
                gravel = new Materials_struct();
                gravel->noice = RNG::get_noice(gravel->brush_size, 0.9);
                gravel->cell_size = 2;
                gravel->brush_size = 5;
                gravel->friction = 0.8;
                gravel->velocity = 1;
                gravel->color = { 128, 128, 128 };
                gravel->liquid = false;
                gravel->direction = false;
            }
            return gravel;
        case WATER:
            if (water == NULL) {
                water = new Materials_struct();
                water->noice = RNG::get_noice(water->brush_size, 1);
                water->cell_size = 2;
                water->brush_size = 5;
                water->friction = 0;
                water->velocity = 1;
                water->color = { 0, 0, 255 };
                water->liquid = true;
                water->direction = false;
            }
            return water;
        case NONE:
            if (none == NULL) {
                none = new Materials_struct();
                none->noice = RNG::get_noice(none->brush_size, 1);
                none->cell_size = 2;
                none->brush_size = 10;
                none->friction = 0;
                none->velocity = 0;
                none->color = { 0, 0, 0 };
                none->liquid = false;
                none->direction = false;
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
}