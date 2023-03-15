#ifndef RNG_H
#define RNG_H

#include <stdlib.h>
#include <time.h>

class RNG {
    protected:
        static RNG* instance;
    public:
        static void get_instance();
        static int get_int(int, int);
        static bool* get_noice(int, double);
};

#endif