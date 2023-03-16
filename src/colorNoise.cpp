#include <iostream>
#include "RNG.h"

using namespace std;

int RNGcolor() {
    return RNG::get_int(167, 180);
}