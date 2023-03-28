#include "renderer.h"

using namespace std;

bool Renderer::run() {
    Uint64 ticksA = 0, ticksB = 0, ticksDelta;
    bool quit = false;
    bool mousePressed = false;
    SDL_Event e;
    Material mat = SAND;
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
                    dy -= SCREEN_PADDING;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mousePressed = false;
                    break;
                case SDL_MOUSEWHEEL:
                    if (e.wheel.y > 0) {
                        if (brush_size < 95) {
                            brush_size += 2;
                        } else {
                            break;
                        }
                    } else if (e.wheel.y < 0) {
                        if (brush_size > 3) {
                            brush_size -= 2;
                        } else {
                            break;
                        }
                    }

                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_1:
                            mat = SAND;
                            mat_text = SAND_HEADER;
                            break;
                        case SDLK_2:
                            mat = GRAVEL;
                            mat_text = GRAVEL_HEADER;
                            break;
                        case SDLK_3:
                            mat = WATER;
                            mat_text = WATER_HEADER;
                            break;
                        case SDLK_4:
                            mat = WALL;
                            mat_text = WALL_HEADER;
                            break;
                        case SDLK_5:    
                            mat = OIL;
                            mat_text = OIL_HEADER;
                            break;
                        case SDLK_r:
                            cout << "Resetting grid..." << endl;
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