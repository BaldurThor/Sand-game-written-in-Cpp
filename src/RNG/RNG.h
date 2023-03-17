#ifndef SAND_RNG_H
#define SAND_RNG_H

#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "../color/colorNoise.h"

class RNG {
    protected:
        static RNG* instance;
        int get_neg_int(int, int);
    public:
        static void get_instance();
        static void free_instance();
        static int get_int(int, int);
        static bool* get_noise(int, double);
        static bool get_bool();
        static bool get_bool(double);
        static ColorNoise get_color_noise();
};

#endif