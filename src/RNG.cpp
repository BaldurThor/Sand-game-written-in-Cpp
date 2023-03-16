#include "RNG.h"

#include <iostream>

RNG* RNG::instance = NULL;

void RNG::get_instance() {
    if (instance == NULL) {
        instance = new RNG();
        srand (time(NULL));
    }
}

void RNG::free_instance() {
    if (instance != NULL) {
        delete instance;
    }
}

int RNG::get_int(int min, int max) {
    if (instance == NULL) {
        get_instance();
    }
    return rand() % (max - min + 1) + min;
}

bool* RNG::get_noice(int size, double density) {
    if (instance == NULL) {
        get_instance();
    }
    bool* noice = new bool[size*size];
    for (int i = 0; i < size*size; i++) {
        noice[i] = rand() % 2;
    }
    return noice;
}

bool RNG::get_bool() {
    if (instance == NULL) {
        get_instance();
    }
    return rand() % 2;
}

bool RNG::get_bool(double factor) {
    if (factor == 0) {
        return true;
    }
    if (instance == NULL) {
        get_instance();
    }
    double X=((double)rand()/(double)RAND_MAX);
    return X < factor;
}

Color RNG::get_color() {
    if (instance == NULL) {
        get_instance();
    }
    Color color;
    color.r = get_int(0, 20) - 10;
    color.g = get_int(0, 20) - 10;
    color.b = get_int(0, 20) - 10;
    return color;
}