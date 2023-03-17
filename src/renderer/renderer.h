#ifndef SAND_RENDERER_H
#define SAND_RENDERER_H

#include <iostream>
#include <stdexcept>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "../materials/materialsStruct.h"
#include "../consts.h"
#include "../color/colorMixer.h"

class Renderer {
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        int brush_size = 5; // must be odd
        const char *mat_text;
        Pixle grid[GRID_WIDTH][GRID_HEIGHT] = { NONE };
        SDL_Color background_color = {242,240,229};
        bool scan_direction = true;
    protected:
        void render();

        void UI_layer();

        void draw_text(const char *text, int posx, int posy, int size, SDL_Color color);
        void draw_text(const char *text, int posx, int posy, int size);
        void draw_text(const char *text, int posx, int posy);
        void draw_text(const int text, int posx, int posy, int size, SDL_Color color);
        void draw_text(const int text, int posx, int posy, int size);
        void draw_text(const int text, int posx, int posy);
        
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
    public:
        Renderer();
        ~Renderer();
        void run();

};

#endif