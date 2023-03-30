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
                SDL_Rect fillRect = {width * screen->grid_cell_size, height * screen->grid_cell_size + screen->padding, screen->grid_cell_size, screen->grid_cell_size};
                SDL_Color color = add_noise(mat->color, pixle.color_noise);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
                SDL_RenderFillRect(renderer, &fillRect);
            }
        }
    }
    UI_layer(menu);
}

void Renderer::draw_cursor(int dx, int dy, int radius) {
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
        draw_pixel(dx + x, dy - y);
        draw_pixel(dx + x, dy + y);
        draw_pixel(dx - x, dy - y);
        draw_pixel(dx - x, dy + y);
        draw_pixel(dx + y, dy - x);
        draw_pixel(dx + y, dy + x);
        draw_pixel(dx - y, dy - x);
        draw_pixel(dx - y, dy + x);

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
    draw_pixel(dx, dy);
}

void Renderer::UI_layer(bool menu) {
    int x, y;

    // Draw cursor
    SDL_GetMouseState(&x, &y);

    // Draw header and footer
    SDL_Rect headerRect = { 0, 0, screen->width, screen->padding };
    SDL_SetRenderDrawColor(renderer, HEADER_COLOR.r, HEADER_COLOR.g, HEADER_COLOR.b, 0x9f);
    SDL_RenderFillRect(renderer, &headerRect);
    SDL_Rect footerRect = { 0, screen->height - screen->padding, screen->width, screen->padding };
    SDL_SetRenderDrawColor(renderer, HEADER_COLOR.r, HEADER_COLOR.g, HEADER_COLOR.b, 0x9f);
    SDL_RenderFillRect(renderer, &footerRect);

    // Draw texts
    if (!menu) {
        sand_button->update(x, y);
        gravel_button->update(x, y);
        water_button->update(x, y);
        oil_button->update(x, y);
        wall_button->update(x, y);
    }

    SDL_Color sand_button_color = sand_button->get_color();
    SDL_Color gravel_button_color = gravel_button->get_color();
    SDL_Color water_button_color = water_button->get_color();
    SDL_Color oil_button_color = oil_button->get_color();
    SDL_Color wall_button_color = wall_button->get_color();

    switch (mat) {
        case SAND:
            sand_button_color = SELECTED_TEXT_COLOR;
            break;
        case GRAVEL:
            gravel_button_color = SELECTED_TEXT_COLOR;
            break;
        case WATER:
            water_button_color = SELECTED_TEXT_COLOR;
            break;
        case OIL:
            oil_button_color = SELECTED_TEXT_COLOR;
            break;
        case WALL:
            wall_button_color = SELECTED_TEXT_COLOR;
            break;
        case NONE:
            break;
    }

    draw_text(SAND_HEADER, screen->text_padding, screen->text_padding, screen->material_button_font_size, sand_button_color);
    draw_text(GRAVEL_HEADER, screen->text_padding + screen->material_button_font_size * 5, screen->text_padding, screen->material_button_font_size, gravel_button_color);
    draw_text(WATER_HEADER, screen->text_padding + screen->material_button_font_size * 12, screen->text_padding, screen->material_button_font_size, water_button_color);
    draw_text(OIL_HEADER, screen->text_padding + screen->material_button_font_size * 18, screen->text_padding, screen->material_button_font_size, oil_button_color);
    draw_text(WALL_HEADER, screen->text_padding + screen->material_button_font_size * 22, screen->text_padding, screen->material_button_font_size, wall_button_color);


    draw_text(RESET_TEXT, screen->text_padding, screen->height - (screen->material_button_font_size), screen->how_to_play_font_size);
    draw_text(brush_size, screen->width - ((2 * screen->material_button_font_size) + screen->text_padding), screen->text_padding, screen->material_button_font_size);
    SDL_Rect play_pause_rect = mediaHandler->get_play_pause_rect();
    SDL_RenderCopy(renderer, mediaHandler->get_play_pause_texture(), &play_pause_rect, &screen->music_button_rect);
    
    if (menu) {
        //draw menu texts
        SDL_Rect fadeRect = { 0, 0, screen->width, screen->height };
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x20);
        SDL_RenderFillRect(renderer, &fadeRect);
        SDL_RenderCopy(renderer, mediaHandler->get_logo_texture(), NULL, &screen->logo_rect);
        if (!how_to_play) {
            start_button->update(x, y);
            how_to_play_button->update(x, y);
            resize_button->update(x, y);
            exit_button->update(x, y);
        }
        draw_text(MENU_START, (screen->width/2) + (3 * screen->button_font_size) - (5.5 * screen->button_font_size), (screen->height/2) - 2 * screen->button_font_size, screen->button_font_size , start_button->get_color());
        draw_text(MENU_HOW_TO_PLAY, (screen->width/2) - (5.5 * screen->button_font_size), (screen->height/2) - screen->button_font_size, screen->button_font_size, how_to_play_button->get_color());
        draw_text(MENU_RESIZE, (screen->width/2) + (2.5 * screen->button_font_size) - (5.5 * screen->button_font_size), (screen->height/2), screen->button_font_size, resize_button->get_color());
        draw_text(MENU_EXIT, (screen->width/2) + (3.5 * screen->button_font_size) - (5.5 * screen->button_font_size), (screen->height/2) + screen->button_font_size, screen->button_font_size , exit_button->get_color());
        if (how_to_play) {
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xbf);
            SDL_RenderFillRect(renderer, &screen->how_to_play_rect);
            //add lines
            draw_text("HOW TO PLAY",                                                    (screen->width/2) - (31 * screen->how_to_play_font_size), (screen->height/2) - (7.5 * screen->how_to_play_font_size), screen->how_to_play_font_size , BG_COLOR);
            draw_text("Use the left mouse button to draw materials on the screen.",     (screen->width/2) - (31 * screen->how_to_play_font_size), (screen->height/2) - (5.5 * screen->how_to_play_font_size), screen->how_to_play_font_size , BG_COLOR);
            draw_text("Use the right mouse button to erase materials from the screen.", (screen->width/2) - (31 * screen->how_to_play_font_size), (screen->height/2) - (3.5 * screen->how_to_play_font_size), screen->how_to_play_font_size , BG_COLOR);
            draw_text("Use the mouse wheel to change the brush size",                   (screen->width/2) - (31 * screen->how_to_play_font_size), (screen->height/2) - (1.5 * screen->how_to_play_font_size), screen->how_to_play_font_size , BG_COLOR);
            draw_text("Select a material from the top of the screen",                   (screen->width/2) - (31 * screen->how_to_play_font_size), (screen->height/2) + (0.5 * screen->how_to_play_font_size), screen->how_to_play_font_size , BG_COLOR);
            draw_text("or with the \'1\' \'2\' \'3\' \'4\' \'5\' keys.",                (screen->width/2) - (31 * screen->how_to_play_font_size), (screen->height/2) + (2.5 * screen->how_to_play_font_size), screen->how_to_play_font_size , BG_COLOR);
            draw_text("Press the \'r\' key to reset the simulation.",                   (screen->width/2) - (31 * screen->how_to_play_font_size), (screen->height/2) + (4.5 * screen->how_to_play_font_size), screen->how_to_play_font_size , BG_COLOR);
            draw_text("Press the escape key to return to the main menu.",               (screen->width/2) - (31 * screen->how_to_play_font_size), (screen->height/2) + (6.5 * screen->how_to_play_font_size), screen->how_to_play_font_size , BG_COLOR);
        }
    }

    draw_cursor(x, y, brush_size);
    SDL_RenderPresent(renderer);
}

void Renderer::draw_text(const char *text, int posx, int posy, int size, SDL_Color color) {
    TTF_Font *font = TTF_OpenFont(FONT_PATH, size);
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
    draw_text(text, posx, posy, 32, { TEXT_COLOR.r, TEXT_COLOR.g, TEXT_COLOR.b });
}

void Renderer::draw_text(const int text, int posx, int posy, int size, SDL_Color color) {
    draw_text(to_string(text).c_str(), posx, posy, size, color);
}

void Renderer::draw_text(const int text, int posx, int posy, int size) {
    draw_text(to_string(text).c_str(), posx, posy, size, { TEXT_COLOR.r, TEXT_COLOR.g, TEXT_COLOR.b });
}

void Renderer::draw_text(const int text, int posx, int posy) {
    draw_text(to_string(text).c_str(), posx, posy, 32, { TEXT_COLOR.r, TEXT_COLOR.g, TEXT_COLOR.b });
}