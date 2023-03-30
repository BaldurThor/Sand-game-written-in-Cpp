#include "button.h"

Button::Button(SDL_Rect rect, SDL_Color default_color, SDL_Color hover_color) {
    this->rect = rect;
    this->default_color = default_color;
    this->hover_color = hover_color;
    this->current_color = default_color;
}

void Button::update(int x, int y) {
    if (within(x, y)) {
        current_color = hover_color;
    } else {
        current_color = default_color;
    }
}

SDL_Color Button::get_color() {
    return current_color;
}

bool Button::within(int x, int y) {
    return x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h;
}

void Button::set_rect(SDL_Rect rect) {
    this->rect = rect;
}