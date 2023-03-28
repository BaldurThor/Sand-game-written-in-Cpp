#include "renderer.h"

using namespace std;

bool Renderer::run() {
    Uint64 ticksA = 0, ticksB = 0, ticksDelta;
    bool quit = false;
    bool mousePressed = false;
    SDL_Event e;
    int x, y, dx, dy;

    while (!quit) {
        ticksA = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
                    return true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mousePressed = true;
                    SDL_GetMouseState(&dx, &dy);
                    if (sand_button->within(dx, dy)) {
                        mat = SAND;
                    } else if (gravel_button->within(dx, dy)) {
                        mat = GRAVEL;
                    } else if (water_button->within(dx, dy)) {
                        mat = WATER;
                    } else if (oil_button->within(dx, dy)) {
                        mat = OIL;
                    } else if (wall_button->within(dx, dy)) {
                        mat = WALL;
                    }
                    dy -= SCREEN_PADDING;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mousePressed = false;
                    break;
                case SDL_MOUSEWHEEL:
                    if (e.wheel.y > 0) {
                        if (brush_size < 95) {
                            brush_size += GRID_CELL_SIZE;
                        } else {
                            break;
                        }
                    } else if (e.wheel.y < 0) {
                        if (brush_size > 5) {
                            brush_size -= GRID_CELL_SIZE;
                        } else {
                            break;
                        }
                    }

                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_1:
                            mat = SAND;
                            break;
                        case SDLK_2:
                            mat = GRAVEL;
                            break;
                        case SDLK_3:
                            mat = WATER;
                            break;
                        case SDLK_4:    
                            mat = OIL;
                            break;
                        case SDLK_5:
                            mat = WALL;
                            break;
                        case SDLK_r:
                            reset_grid();
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        if (mousePressed) {
            if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                y -= SCREEN_PADDING;
                fill_grid(x, y, dx, dy, mat);
                dx = x;
                dy = y;
            }
            else {
                y -= SCREEN_PADDING;
                fill_grid(x, y, dx ,dy, NONE);
                dx = x;
                dy = y;
            }
        }
        ticksDelta = ticksA - ticksB;
        if (ticksDelta > TICK_RATE) {
            ticksB = ticksA;
            update();
            render(false);
        }
    }
    return false;
}