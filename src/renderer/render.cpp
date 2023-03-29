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
    SDL_Rect headerRect = { 0, 0, SCREEN_WIDTH, SCREEN_PADDING };
    SDL_SetRenderDrawColor(renderer, HEADER_COLOR.r, HEADER_COLOR.g, HEADER_COLOR.b, 0x9f);
    SDL_RenderFillRect(renderer, &headerRect);
    SDL_Rect footerRect = { 0, SCREEN_HEIGHT - SCREEN_PADDING, SCREEN_WIDTH, SCREEN_PADDING };
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

    draw_text(SAND_HEADER, TEXT_PADDING, TEXT_PADDING, MATERIAL_BUTTON_FONT_SIZE, sand_button_color);
    draw_text(GRAVEL_HEADER, TEXT_PADDING + MATERIAL_BUTTON_FONT_SIZE * 5, TEXT_PADDING, MATERIAL_BUTTON_FONT_SIZE, gravel_button_color);
    draw_text(WATER_HEADER, TEXT_PADDING + MATERIAL_BUTTON_FONT_SIZE * 12, TEXT_PADDING, MATERIAL_BUTTON_FONT_SIZE, water_button_color);
    draw_text(OIL_HEADER, TEXT_PADDING + MATERIAL_BUTTON_FONT_SIZE * 18, TEXT_PADDING, MATERIAL_BUTTON_FONT_SIZE, oil_button_color);
    draw_text(WALL_HEADER, TEXT_PADDING + MATERIAL_BUTTON_FONT_SIZE * 22, TEXT_PADDING, MATERIAL_BUTTON_FONT_SIZE, wall_button_color);


    draw_text(RESET_TEXT, TEXT_PADDING, SCREEN_HEIGHT - (MATERIAL_BUTTON_FONT_SIZE), HOW_TO_PLAY_FONT_SIZE);
    draw_text(brush_size, SCREEN_WIDTH - ((2 * MATERIAL_BUTTON_FONT_SIZE) + TEXT_PADDING), TEXT_PADDING, MATERIAL_BUTTON_FONT_SIZE);
    SDL_Rect play_pause_rect = mediaHandler->get_play_pause_rect();
    SDL_RenderCopy(renderer, mediaHandler->get_play_pause_texture(), &play_pause_rect, &MUSIC_BUTTON_RECT);
    
    if (menu) {
        //draw menu texts
        SDL_Rect fadeRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x20);
        SDL_RenderFillRect(renderer, &fadeRect);
        SDL_RenderCopy(renderer, mediaHandler->get_logo_texture(), NULL, &LOGO_RECT);
        if (!how_to_play) {
            start_button->update(x, y);
            how_to_play_button->update(x, y);
            exit_button->update(x, y);
        }
        draw_text("START", (SCREEN_WIDTH/2) + (3 * BUTTON_FONT_SIZE) - (5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2) - 2 * BUTTON_FONT_SIZE, BUTTON_FONT_SIZE , start_button->get_color());
        draw_text("HOW TO PLAY", (SCREEN_WIDTH/2) - (5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2) - BUTTON_FONT_SIZE, BUTTON_FONT_SIZE, how_to_play_button->get_color());
        draw_text("EXIT", (SCREEN_WIDTH/2) + (3.5 * BUTTON_FONT_SIZE) - (5.5 * BUTTON_FONT_SIZE), (SCREEN_HEIGHT/2), BUTTON_FONT_SIZE , exit_button->get_color());
        if (how_to_play) {
            SDL_Rect howToPlayRect = { (SCREEN_WIDTH/2) - (HOW_TO_PLAY_WIDTH/2), (SCREEN_HEIGHT/2) - (HOW_TO_PLAY_HEIGHT/2), HOW_TO_PLAY_WIDTH, HOW_TO_PLAY_HEIGHT };
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xbf);
            SDL_RenderFillRect(renderer, &howToPlayRect);
            //add lines
            draw_text("HOW TO PLAY",                                                    (SCREEN_WIDTH/2) - (31 * HOW_TO_PLAY_FONT_SIZE), (SCREEN_HEIGHT/2) - (7.5 * HOW_TO_PLAY_FONT_SIZE), HOW_TO_PLAY_FONT_SIZE , BG_COLOR);
            draw_text("Use the left mouse button to draw materials on the screen.",     (SCREEN_WIDTH/2) - (31 * HOW_TO_PLAY_FONT_SIZE), (SCREEN_HEIGHT/2) - (5.5 * HOW_TO_PLAY_FONT_SIZE), HOW_TO_PLAY_FONT_SIZE , BG_COLOR);
            draw_text("Use the right mouse button to erase materials from the screen.", (SCREEN_WIDTH/2) - (31 * HOW_TO_PLAY_FONT_SIZE), (SCREEN_HEIGHT/2) - (3.5 * HOW_TO_PLAY_FONT_SIZE), HOW_TO_PLAY_FONT_SIZE , BG_COLOR);
            draw_text("Use the mouse wheel to change the brush size",                   (SCREEN_WIDTH/2) - (31 * HOW_TO_PLAY_FONT_SIZE), (SCREEN_HEIGHT/2) - (1.5 * HOW_TO_PLAY_FONT_SIZE), HOW_TO_PLAY_FONT_SIZE , BG_COLOR);
            draw_text("Select a material from the top of the screen",                   (SCREEN_WIDTH/2) - (31 * HOW_TO_PLAY_FONT_SIZE), (SCREEN_HEIGHT/2) + (0.5 * HOW_TO_PLAY_FONT_SIZE), HOW_TO_PLAY_FONT_SIZE , BG_COLOR);
            draw_text("or with the \'1\' \'2\' \'3\' \'4\' \'5\' keys.",                (SCREEN_WIDTH/2) - (31 * HOW_TO_PLAY_FONT_SIZE), (SCREEN_HEIGHT/2) + (2.5 * HOW_TO_PLAY_FONT_SIZE), HOW_TO_PLAY_FONT_SIZE , BG_COLOR);
            draw_text("Press the \'r\' key to reset the simulation.",                   (SCREEN_WIDTH/2) - (31 * HOW_TO_PLAY_FONT_SIZE), (SCREEN_HEIGHT/2) + (4.5 * HOW_TO_PLAY_FONT_SIZE), HOW_TO_PLAY_FONT_SIZE , BG_COLOR);
            draw_text("Press the escape key to return to the main menu.",               (SCREEN_WIDTH/2) - (31 * HOW_TO_PLAY_FONT_SIZE), (SCREEN_HEIGHT/2) + (6.5 * HOW_TO_PLAY_FONT_SIZE), HOW_TO_PLAY_FONT_SIZE , BG_COLOR);
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