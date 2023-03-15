#include "materials.h"

Materials_struct::Materials_struct(Material material) {
    switch (material) {
        case SAND:
            noice = RNG::get_noice(5, 0.5);
            cell_size = 2;
            brush_size = 5;
            friction = 0.2;
            velocity = 1;
            color = { 255, 255, 0 };
            break;
        case GRAVEL:
            noice = RNG::get_noice(3, 0.7);
            cell_size = 4;
            brush_size = 3;
            friction = 0.8;
            velocity = 1;
            color = { 127, 127, 127 };
            break;
        case NONE:
            break;
    }
}

Materials_struct::~Materials_struct() {
    if (noice != NULL) {
        delete noice;
    }
}