#include "renderer.h"

using namespace std;

bool Renderer::run() {
    Uint64 ticksA = 0, ticksB = 0, ticksDelta;
    bool quit = false;
    bool mousePressed = false;
    int index = 1;
    SDL_Event e;
    int x, y, dx, dy;

    while (!quit) {
        ticksA = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    return true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    fx_playing = true;
                    fx_play = true;
                    mousePressed = true;
                    SDL_GetMouseState(&dx, &dy);
                    if (sand_button->within(dx, dy)) {
                        index = 1;
                        mat = SAND;
                    } else if (gravel_button->within(dx, dy)) {
                        index = 2;
                        mat = GRAVEL;
                    } else if (water_button->within(dx, dy)) {
                        index = 3;
                        mat = WATER;
                    } else if (oil_button->within(dx, dy)) {
                        index = 4;
                        mat = OIL;
                    } else if (wall_button->within(dx, dy)) {
                        index = 5;
                        mat = WALL;
                    } else if (music_button->within(dx, dy)) {
                        if (music_on) {
                            mediaHandler->pause_music();
                        }
                        else {
                            mediaHandler->continue_music();
                        }
                        music_on = !music_on;
                    }
                    dy -= SCREEN_PADDING;
                    break;
                case SDL_MOUSEBUTTONUP:
                    fx_playing = false;
                    mediaHandler->stop_sound();
                    mousePressed = false;
                    break;
                case SDL_MOUSEWHEEL:
                    if (e.wheel.y > 0) {
                        if (brush_size < 50) {
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
                            if (fx_playing) {
                                mediaHandler->stop_sound();
                                fx_play = true;
                            }
                            index = 1;
                            mat = SAND;
                            break;
                        case SDLK_2:
                            if (fx_playing) {
                                mediaHandler->stop_sound();
                                fx_play = true;
                            }
                            index = 2;
                            mat = GRAVEL;
                            break;
                        case SDLK_3:
                            if (fx_playing) {
                                mediaHandler->stop_sound();
                                fx_play = true;
                            }
                            index = 3;
                            mat = WATER;
                            break;
                        case SDLK_4:
                            if (fx_playing) {
                                mediaHandler->stop_sound();
                                fx_play = true;
                            }  
                            index = 4;  
                            mat = OIL;
                            break;
                        case SDLK_5:
                            if (fx_playing) {
                                mediaHandler->stop_sound();
                                fx_play = true;
                            }
                            index = 5;
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
                                mediaHandler->pause_music();
                            }
                            else {
                                mediaHandler->continue_music();
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
                if (fx_play && grid_button->within(x, y)) {
                    mediaHandler->play_sound(index);
                    fx_play = false;
                }
                if (fx_playing && !grid_button->within(x, y)) {
                    mediaHandler->stop_sound();
                    fx_play = true;
                }
                y -= SCREEN_PADDING;
                fill_grid(x, y, dx, dy, mat);
                dx = x;
                dy = y;
            }
            else {
                if (fx_play && grid_button->within(x, y)) {
                    mediaHandler->play_sound(0);
                    fx_play = false;
                }
                if (fx_playing && !grid_button->within(x, y)) {
                    mediaHandler->stop_sound();
                    fx_play = true;
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