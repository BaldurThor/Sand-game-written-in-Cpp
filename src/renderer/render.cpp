#include "renderer.h"

using namespace std;

void Renderer::render() {
    SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 255);
    SDL_RenderClear(renderer);
    Materials_struct* mat;

    for (int height = 0; height < GRID_HEIGHT; height++) {
        for (int width = 0; width < GRID_WIDTH; width++) {
            Pixle pixle = grid[width][height];
            if (pixle.material != NONE) {
                mat = Materials_struct::get_instance(pixle);
                SDL_Rect fillRect = {width * GRID_CELL_SIZE, height * GRID_CELL_SIZE + SCREEN_PADDING, GRID_CELL_SIZE, GRID_CELL_SIZE};
                SDL_Color color = add_noise(mat->color, pixle.color_noise);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
                SDL_RenderFillRect(renderer, &fillRect);
            }
        }
    }

    draw_text(header, 4, 4);
    draw_text("Press R to reset", 4, SCREEN_HEIGHT - 12, 12, { 0, 0, 0 });
    draw_text(brush_size, SCREEN_WIDTH - 12, 4, 12, { 0, 0, 0 });
    SDL_RenderPresent(renderer);
}

void Renderer::draw_text(const char *text, int posx, int posy, int size, SDL_Color color) {
    TTF_Font *font = TTF_OpenFont("dogica.ttf", size);
    if (font == NULL) {
        cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
        return;
    }
    SDL_Color textColor = { color.r, color.g, color.b };
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == NULL) {
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
        TTF_CloseFont(font);
        return;
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }
    SDL_Rect textRect = { posx, posy, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

void Renderer::draw_text(const char *text, int posx, int posy, int size) {
    draw_text(text, posx, posy, size, { 0, 0, 0 });
}

void Renderer::draw_text(const char *text, int posx, int posy) {
    draw_text(text, posx, posy, 16, { 0, 0, 0 });
}

void Renderer::draw_text(const int text, int posx, int posy, int size, SDL_Color color) {
    draw_text(to_string(text).c_str(), posx, posy, size, color);
}

void Renderer::draw_text(const int text, int posx, int posy, int size) {
    draw_text(to_string(text).c_str(), posx, posy, size, { 0, 0, 0 });
}

void Renderer::draw_text(const int text, int posx, int posy) {
    draw_text(to_string(text).c_str(), posx, posy, 16, { 0, 0, 0 });
}