#include "renderer.h"

void Renderer::menu() {
    Uint64 ticksA = 0, ticksB = 0, ticksDelta;
    bool quit = false;
    SDL_Event e;
    int x, y;

    while (!quit) {
        ticksA = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x, &y);
                    if (how_to_play) {
                        how_to_play = false;
                    } 
                    else {
                        if (start_button->within(x, y)) {
                            quit = run();
                        } else if (how_to_play_button->within(x, y)) {
                            how_to_play = true;
                        } else if (exit_button->within(x, y)) {
                            quit = true;
                        } else if (music_button->within(x, y)) {
                            if (music_on) {
                                Mix_PauseMusic();
                            }
                            else {
                                Mix_ResumeMusic();
                            }
                            music_on = !music_on;
                        }

                    }
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            if (how_to_play) {
                                how_to_play = false;
                            } else {
                                quit = run();
                            }
                            break;
                        case SDLK_0:
                            if (music_on) {
                                Mix_PauseMusic();
                            }
                            else {
                                Mix_ResumeMusic();
                            }
                            music_on = !music_on;
                    }
                    break;
            }
        }
        ticksDelta = ticksA - ticksB;
        if (ticksDelta > TICK_RATE) {
            ticksB = ticksA;
            render(true);
        }
    }
}