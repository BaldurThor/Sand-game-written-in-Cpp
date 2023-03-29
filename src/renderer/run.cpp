#include "renderer.h"

using namespace std;

bool Renderer::run() {
    Uint64 ticksA = 0, ticksB = 0, ticksDelta;
    bool quit = false;
    bool mousePressed = false;
    int index = 0;
    SDL_Event e;
    int x, y, dx, dy;
    Mix_Chunk *sounds[5] = {sand_sound, gravel_sound, water_sound, oil_sound, wall_sound};

    while (!quit) {
        ticksA = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
                    return true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    sound_on = true;
                    mousePressed = true;
                    SDL_GetMouseState(&dx, &dy);
                    if (sand_button->within(dx, dy)) {
                        index = 0;
                        mat = SAND;
                    } else if (gravel_button->within(dx, dy)) {
                        index = 1;
                        mat = GRAVEL;
                    } else if (water_button->within(dx, dy)) {
                        index = 2;
                        mat = WATER;
                    } else if (oil_button->within(dx, dy)) {
                        index = 3;
                        mat = OIL;
                    } else if (wall_button->within(dx, dy)) {
                        index = 4;
                        mat = WALL;
                    } else if (music_button->within(dx, dy)) {
                        if (music_on) {
                            Mix_PauseMusic();
                        }
                        else {
                            Mix_ResumeMusic();
                        }
                        music_on = !music_on;
                    }
                    dy -= SCREEN_PADDING;
                    break;
                case SDL_MOUSEBUTTONUP:
                    Mix_HaltChannel(-1);
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
                            index = 0;
                            mat = SAND;
                            break;
                        case SDLK_2:
                            index = 1;
                            mat = GRAVEL;
                            break;
                        case SDLK_3:
                            index = 2;
                            mat = WATER;
                            break;
                        case SDLK_4:  
                            index = 3;  
                            mat = OIL;
                            break;
                        case SDLK_5:
                            index = 4;
                            mat = WALL;
                            break;
                        case SDLK_r:
                            reset_grid();
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_0:
                            if (music_on) {
                                Mix_PauseMusic();
                            }
                            else {
                                Mix_ResumeMusic();
                            }
                            music_on = !music_on;
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
                if (sound_on && grid_button->within(x, y)) {
                    Mix_PlayChannel(-1, sounds[index], -1);
                    sound_on = false;
                }
                y -= SCREEN_PADDING;
                fill_grid(x, y, dx, dy, mat);
                dx = x;
                dy = y;
            }
            else {
                if (sound_on && grid_button->within(x, y)) {
                    Mix_PlayChannel(-1, sounds[0], -1);
                    sound_on = false;
                }
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