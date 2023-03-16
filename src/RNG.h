#ifndef RNG_H
#define RNG_H

#include <stdlib.h>
#include <time.h>
#include <stdint.h>

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

class RNG {
    protected:
        static RNG* instance;
    public:
        static void get_instance();
        static void free_instance();
        static int get_int(int, int);
        static bool* get_noice(int, double);
        static bool get_bool();
        static bool get_bool(double);
        static Color get_color();
};

#endif