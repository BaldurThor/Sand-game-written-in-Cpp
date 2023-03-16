#include <iostream>
#include "SDL2/SDL.h"
#include "consts.h"
#include "materials.h"
#include "SDL2/SDL_ttf.h"

using namespace std;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool scan_direction = true;

Pixle grid[GRID_WIDTH][GRID_HEIGHT] = { NONE };

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    window = SDL_CreateWindow("Sand Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    
    if (TTF_Init() < 0) {
        cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    TTF_Quit();
    SDL_Quit();
    RNG::free_instance();
    Materials_struct::free_instance();
}

void draw_text(char *text) {
    TTF_Font *font = TTF_OpenFont("dogica.ttf", 16);
    if (font == NULL) {
        cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
        return;
    }
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == NULL) {
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
        return;
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
        return;
    }
    SDL_Rect textRect = { 0, 0, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

bool update_move(int width, int height, Pixle pixle, int velocity, int height_mod) {
    if ((width + velocity < 0) || (width + velocity > GRID_WIDTH - 1)) {
            return false;
    }
    if (0 < velocity) {
        for (int i = 1; i <= velocity; i++) {
            if (grid[width + i][height + height_mod] != NONE && grid[width + i][height + height_mod] != pixle) {
                return false;
            }
        }
    }
    else {
        for (int i = -velocity; i > 0; i--) {
            if (grid[width - i][height + height_mod] != NONE && grid[width - i][height + height_mod] != pixle) {
                return false;
            }
        }
    }
    if (grid[width + velocity][height + height_mod] == NONE) {
        grid[width + velocity][height + height_mod] = pixle;
        grid[width][height].material = NONE;
        return true;
    }
    return false;
}

void update_helper(int width, int height) {
    if (grid[width][height].material != NONE) {
        Pixle pixle = grid[width][height];
        Materials_struct *mat_struct = Materials_struct::get_instance(pixle);
        if (height == GRID_HEIGHT - 1 || mat_struct->immovable) {
            return;
        }

        Pixle other_pixle = grid[width][height + 1];
        Materials_struct *other_mat_struct = Materials_struct::get_instance(other_pixle);

        if (pixle.velocity > other_mat_struct->weight) {
            pixle.velocity -= other_mat_struct->friction;
            grid[width][height + 1] = pixle;
            grid[width][height] = other_pixle;
            return;
        }

        /*if (grid[width][height + 1] == NONE || (mat != WATER && grid[width][height + 1] == WATER)) {
            mat_place = grid[width][height + 1];
            grid[width][height + 1] = mat;
            grid[width][height] = mat_place;
            return;
        }*/
        int height_mod = 1;
        if (mat_struct->liquid) {
            height_mod = 0;
        }
        int velocity = RNG::get_int(1, mat_struct->velocity);
        if (scan_direction) {
            if (!update_move(width, height, pixle, velocity, height_mod)) {
                update_move(width, height, pixle, -velocity, height_mod);
            }
        }
        else {
            if (!update_move(width, height, pixle, -velocity, height_mod)) {
                update_move(width, height, pixle, velocity, height_mod);
            }
        }
    }
}

void update() {
    for (int height = GRID_HEIGHT - 1; height >= 0; height--) {
        if (scan_direction) {
            for (int width = 0; width < GRID_WIDTH; width++) {
                update_helper(width, height);
            }
        }
        else {
            for (int width = GRID_WIDTH - 1; width >= 0; width--) {
                update_helper(width, height);
            }
        }
    }
    scan_direction = !scan_direction;
}

void render() {
    SDL_SetRenderDrawColor(renderer, 242, 240, 229, 255);
    SDL_RenderClear(renderer);
    Materials_struct* mat;

    for (int height = 0; height < GRID_HEIGHT; height++) {
        for (int width = 0; width < GRID_WIDTH; width++) {
            if (grid[width][height].material != NONE) {
                mat = Materials_struct::get_instance(grid[width][height]);
                SDL_Rect fillRect = {width * GRID_CELL_SIZE, height * GRID_CELL_SIZE, GRID_CELL_SIZE, GRID_CELL_SIZE};
                SDL_SetRenderDrawColor(renderer, mat->color.r, mat->color.g, mat->color.b, 0xFF);
                SDL_RenderFillRect(renderer, &fillRect);
            }
        }
    }

    draw_text("SAND");
    SDL_RenderPresent(renderer);
}

void fill(int x, int y, int dx, int dy, Material state) {
    /*
    if (dx < x) {
        int temp = x;
        x = dx;
        dx = temp;
    }
    if (dy < y) {
        int temp = y;
        y = dy;
        dy = temp;
    }
    bool sml_grid[dx-x][dy-y] = { false };
    int ddx = dx - x;
    int ddy = dy - y;
    */

    int brush_size = BRUSH_SIZE / 2;
    for (int xi = x - brush_size; xi < x + brush_size; xi++) {
        for (int yi = y - brush_size; yi < y + brush_size; yi++) {
            if (xi < SCREEN_WIDTH && yi < SCREEN_HEIGHT && xi >= 0 && yi >= 0) {
                if (grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].material == NONE || state == NONE) {
                    grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].material = state;
                    grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].velocity = Materials_struct::get_instance(state)->weight;
                    grid[xi / GRID_CELL_SIZE][yi / GRID_CELL_SIZE].color = Materials_struct::get_instance(state)->color;
                }
            }
        }
    }
}

void run() {
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
                            break;
                        case SDLK_2:
                            mat = GRAVEL;
                            break;
                        case SDLK_3:
                            mat = WATER;
                            break;
                        case SDLK_4:
                            mat = WALL;
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
                fill(x, y, dx, dy, mat);
                dx = x;
                dy = y;
            }
            else {
                fill(x, y, dx ,dy, NONE);
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

int main(int argc, char* args[]) {
    if (!init()) {
        cout << "Failed to initialize!" << endl;
    }
    else {
        run();
    }
    close();
    return 0;
}
