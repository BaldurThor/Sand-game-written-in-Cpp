#include "RNG.h"

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

int RNG::get_neg_int(int min, int max) {
    if (instance == NULL) {
        get_instance();
    }
    max = max + (min * -1);
    return get_int(0, max) + min;
}

int RNG::get_int(int min, int max) {
    if (instance == NULL) {
        get_instance();
    }
    if (min < 0) {
        return instance->get_neg_int(min, max);
    }
    return rand() % (max - min + 1) + min;
}

bool* RNG::get_noise(int size, double density) {
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
    return rand() > (RAND_MAX / 2);
}

bool RNG::get_bool(double factor) {
    if (factor == 0) {
        return true;
    }
    if (instance == NULL) {
        get_instance();
    }
    double X=((double)rand()/(double)RAND_MAX);
    return X > factor;
}

ColorNoise RNG::get_color_noise() {
    if (instance == NULL) {
        get_instance();
    }
    ColorNoise color;
    color.r = get_int(-10 ,10);
    color.g = get_int(-10 ,10);
    color.b = get_int(-10 ,10);
    return color;
}