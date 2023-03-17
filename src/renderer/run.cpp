#include "renderer.h"

using namespace std;

void Renderer::run() {
    Uint64 ticksA = 0, ticksB = 0, ticksDelta;
    bool quit = false;
    bool mousePressed = false;
    SDL_Event e;
    Material mat = SAND;
    int x, y, dx, dy;
    header = SAND_HEADER;

    while (!quit) {
        ticksA = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mousePressed = true;
                    SDL_GetMouseState(&dx, &dy);
                    break;
                case SDL_MOUSEBUTTONUP:
                    mousePressed = false;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_1:
                            mat = SAND;
                            header = SAND_HEADER;
                            break;
                        case SDLK_2:
                            mat = GRAVEL;
                            header = GRAVEL_HEADER;
                            break;
                        case SDLK_3:
                            mat = WATER;
                            header = WATER_HEADER;
                            break;
                        case SDLK_4:
                            mat = WALL;
                            header = WALL_HEADER;
                            break;
                        case SDLK_r:
                            cout << "Resetting grid..." << endl;
                            reset_grid();
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
            render();
        }
    }
}