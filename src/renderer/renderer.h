#ifndef SAND_RENDERER_H
#define SAND_RENDERER_H

#include <iostream>
#include <stdexcept>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "../materials/materialsStruct.h"
#include "../consts.h"
#include "../color/colorMixer.h"
#include "../button/button.h"

class Renderer {
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Texture *logo_texture;
        Mix_Music *music;
        Mix_Chunk *sand_sound;
        Mix_Chunk *gravel_sound;
        Mix_Chunk *water_sound;
        Mix_Chunk *oil_sound;
        Mix_Chunk *wall_sound;
        Mix_Chunk *remove_sound;
        Mix_Chunk *sounds[6] = {remove_sound, sand_sound, gravel_sound, water_sound, oil_sound, wall_sound};
        int brush_size = 5; // must be odd
        Material mat = SAND;
        Pixle grid[GRID_WIDTH][GRID_HEIGHT] = { NONE };
        SDL_Color background_color = { BG_COLOR.r, BG_COLOR.g, BG_COLOR.b };
        bool scan_direction = true;
        bool how_to_play = false;
        Button *start_button;
        Button *how_to_play_button;
        Button *exit_button;
        Button *sand_button;
        Button *gravel_button;
        Button *water_button;
        Button *oil_button;
        Button *wall_button;
    protected:
        void render(bool);

        void UI_layer(bool);

        void draw_text(const char *text, int posx, int posy, int size, SDL_Color color);
        void draw_text(const char *text, int posx, int posy, int size);
        void draw_text(const char *text, int posx, int posy);
        void draw_text(const int text, int posx, int posy, int size, SDL_Color color);
        void draw_text(const int text, int posx, int posy, int size);
        void draw_text(const int text, int posx, int posy);

        void draw_pixel(int, int);
        void draw_cursor(int, int, int);
        
        void reset_grid();
        void draw_circle(int, int, int, int, Material);
        void bresenham_algo(int, int, Material);
        void fill_grid(int, int, int ,int , Material);
        // both x or both y have to be the same;
        void put_line(int, int, int,int , Material);
        void put_pixle(int, int, Material);

        void update();
        void update_helper(int, int);
        bool update_move(int, int, Pixle, int, int);
        
        bool run();
    public:
        Renderer();
        ~Renderer();
        void menu();
};

#endif