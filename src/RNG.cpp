#include "RNG.h"

RNG* RNG::instance = NULL;

void RNG::get_instance() {
    if (instance == NULL) {
        instance = new RNG();
        srand (time(NULL));
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