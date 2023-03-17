#include "renderer.h"

void Renderer::update() {
    for (int height = GRID_HEIGHT - 1; height >= 0; height--) {
        if (scan_direction) {
            for (int width = 0; width < GRID_WIDTH; width++) {
                update_helper(width, height);
            }
        }
        else {
            for (int width = GRID_WIDTH - 1; width >= 0; width--) {
                update_helper(width, height);
            }
        }
    }
    scan_direction = !scan_direction;
}


void Renderer::update_helper(int width, int height) {
    if (grid[width][height].material != NONE) {
        Pixle pixle = grid[width][height];
        Materials_struct *mat_struct = Materials_struct::get_instance(pixle);
        if (height == GRID_HEIGHT - 1 || mat_struct->immovable) {
            return;
        }

        Pixle other_pixle = grid[width][height + 1];
        Materials_struct *other_mat_struct = Materials_struct::get_instance(other_pixle);

        if (mat_struct->liquid && other_mat_struct->liquid && other_mat_struct->weight < mat_struct->weight) {
            grid[width][height + 1] = pixle;
            grid[width][height] = other_pixle;
            return;
        }

        if (pixle.velocity > other_mat_struct->weight) {
            pixle.velocity -= other_mat_struct->friction;
            grid[width][height + 1] = pixle;
            grid[width][height] = other_pixle;
            return;
        }
        int height_mod = 1;
        if (mat_struct->liquid) {
            height_mod = 0;
        }
        int velocity = RNG::get_int(1, mat_struct->velocity);
        if (scan_direction) {
            if (!update_move(width, height, pixle, velocity, height_mod)) {
                update_move(width, height, pixle, -velocity, height_mod);
            }
        }
        else {
            if (!update_move(width, height, pixle, -velocity, height_mod)) {
                update_move(width, height, pixle, velocity, height_mod);
            }
        }
    }
}

bool Renderer::update_move(int width, int height, Pixle pixle, int velocity, int height_mod) {
    if ((width + velocity < 0) || (width + velocity > GRID_WIDTH - 1)) {
            return false;
    }
    Pixle other_pixle;
    Materials_struct *mat;
    if (0 < velocity) {
        for (int i = 1; i <= velocity; i++) {
            other_pixle = grid[width + i][height + height_mod];
            mat = Materials_struct::get_instance(other_pixle);
            if (other_pixle != NONE && other_pixle != pixle && !mat->liquid) {
                return false;
            }
        }
    }
    else {
        for (int i = -velocity; i > 0; i--) {
            other_pixle = grid[width - i][height + height_mod];
            mat = Materials_struct::get_instance(other_pixle);
            if (other_pixle != NONE && other_pixle != pixle && !mat->liquid) {
                return false;
            }
        }
    }
    other_pixle = grid[width + velocity][height + height_mod];
    mat = Materials_struct::get_instance(other_pixle);
    if ((other_pixle == NONE || mat->liquid) && pixle != other_pixle) {
        grid[width + velocity][height + height_mod] = pixle;
        grid[width][height] = other_pixle;
        return true;
    }
    return false;
}