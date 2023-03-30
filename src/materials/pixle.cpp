#include "pixle.h"

bool Pixle::operator==(const Pixle& other) const {
        return material == other.material;
}

bool Pixle::operator!=(const Pixle& other) const {
    return !(*this == other);
}

bool Pixle::operator==(const Material& other) const {
    return material == other;
}

bool Pixle::operator!=(const Material& other) const {
    return !(*this == other);
}

Pixle Pixle::operator=(const Material& mat) {
    material = mat;
    return *this;
}