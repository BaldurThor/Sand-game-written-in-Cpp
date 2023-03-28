#include "renderer.h"

using namespace std;

void Renderer::render(bool menu) {
    SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 255);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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
    UI_layer(menu);
}

void draw_pixel(SDL_Renderer *renderer, int x, int y) {
    SDL_Rect pixel = { (x / GRID_CELL_SIZE) * GRID_CELL_SIZE, (y / GRID_CELL_SIZE) * GRID_CELL_SIZE, GRID_CELL_SIZE, GRID_CELL_SIZE };
    SDL_RenderFillRect(renderer, &pixel);
}

void draw_cursor(SDL_Renderer* renderer, int dx, int dy, int radius) {
    radius = radius / 2;
    const int32_t diameter = (radius * 2);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x9F);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        // Each of the following renders an octant of the circle
        draw_pixel(renderer, dx + x, dy - y);
        draw_pixel(renderer, dx + x, dy + y);
        draw_pixel(renderer, dx - x, dy - y);
        draw_pixel(renderer, dx - x, dy + y);
        draw_pixel(renderer, dx + y, dy - x);
        draw_pixel(renderer, dx + y, dy + x);
        draw_pixel(renderer, dx - y, dy - x);
        draw_pixel(renderer, dx - y, dy + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }

    }
}

void Renderer::UI_layer(bool menu) {
    int x, y;

    // Draw cursor
    SDL_GetMouseState(&x, &y);
    draw_cursor(renderer, x, y, brush_size);

    // Draw header and footer
    SDL_Rect headerRect = { 0, 0, SCREEN_WIDTH, SCREEN_PADDING };
    SDL_SetRenderDrawColor(renderer, HEADER_COLOR.r, HEADER_COLOR.g, HEADER_COLOR.b, 0x9f);
    SDL_RenderFillRect(renderer, &headerRect);
    SDL_Rect footerRect = { 0, SCREEN_HEIGHT - SCREEN_PADDING, SCREEN_WIDTH, SCREEN_PADDING };
    SDL_SetRenderDrawColor(renderer, HEADER_COLOR.r, HEADER_COLOR.g, HEADER_COLOR.b, 0x9f);
    SDL_RenderFillRect(renderer, &footerRect);

    // Draw texts
    draw_text(mat_text, 4, 4);
    draw_text(RESET_TEXT, 4, SCREEN_HEIGHT - 16, 12);
    draw_text(brush_size, SCREEN_WIDTH - 24, 4, 12);
    if (menu) {
        //draw menu texts
        SDL_Rect fadeRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x20);
        SDL_RenderFillRect(renderer, &fadeRect);
        SDL_RenderCopy(renderer, logo_texture, NULL, &LOGO_RECT);
        start_button->update(x, y);
        how_to_play_button->update(x, y);
        exit_button->update(x, y);

        draw_text("START", (SCREEN_WIDTH/2) + (3 * BUTTON_FONT_SIZE) - (5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2) - 2 * BUTTON_FONT_SIZE, BUTTON_FONT_SIZE , start_button->get_color());
        draw_text("HOW TO PLAY", (SCREEN_WIDTH/2) - (5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2) - BUTTON_FONT_SIZE, BUTTON_FONT_SIZE, how_to_play_button->get_color());
        draw_text("EXIT", (SCREEN_WIDTH/2) + (3.5 * BUTTON_FONT_SIZE) - (5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2), BUTTON_FONT_SIZE , exit_button->get_color());

    }

    SDL_RenderPresent(renderer);
}

void Renderer::draw_text(const char *text, int posx, int posy, int size, SDL_Color color) {
    TTF_Font *font = TTF_OpenFont("dogica.ttf", size);
    if (font == NULL) {
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
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
    draw_text(text, posx, posy, size, { TEXT_COLOR.r, TEXT_COLOR.g, TEXT_COLOR.b });
}

void Renderer::draw_text(const char *text, int posx, int posy) {
    draw_text(text, posx, posy, 16, { TEXT_COLOR.r, TEXT_COLOR.g, TEXT_COLOR.b });
}

void Renderer::draw_text(const int text, int posx, int posy, int size, SDL_Color color) {
    draw_text(to_string(text).c_str(), posx, posy, size, color);
}

void Renderer::draw_text(const int text, int posx, int posy, int size) {
    draw_text(to_string(text).c_str(), posx, posy, size, { TEXT_COLOR.r, TEXT_COLOR.g, TEXT_COLOR.b });
}

void Renderer::draw_text(const int text, int posx, int posy) {
    draw_text(to_string(text).c_str(), posx, posy, 16, { TEXT_COLOR.r, TEXT_COLOR.g, TEXT_COLOR.b });
}