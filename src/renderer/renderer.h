#ifndef SAND_RENDERER_H
#define SAND_RENDERER_H

#include <iostream>
#include <stdexcept>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "../materials/materialsStruct.h"
#include "../consts.h"
#include "../color/colorMixer.h"
#include "../button/button.h"
#include "../media/mediaHandler.h"

class Renderer {
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        MediaHandler *mediaHandler;
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
        Button *music_button;
        Button *grid_button;
        bool music_on = true;
        bool fx_playing = false;
        bool fx_play = false;
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