//
// Created by Rudolf Vrbenský on 07/10/2023.
//


#include <xsFont.h>
#include <xsConstants.h>

#include <SDL.h>
#include <SDL_ttf.h>

xsFont* xsCreateFont(xsCore *core, const char *path_to_ttf, int size, xsColor color, enum xsFontDrawMode mode) {
    xsBasicFont *bFont = (xsBasicFont*)TTF_OpenFont(path_to_ttf, size);
    if (bFont == NULL) {
        printf("ERROR: failed to create font %s err: %s\n", path_to_ttf, SDL_GetError());
        return NULL;
    }
    xsFont* font = malloc(sizeof(xsFont));
    font->font = bFont;
    font->draw_mode = mode;

    font->size = size;
    font->text_color = color;
    font->bg_color = XSUI_COLOR_TRANSPARENT;

    font->core = core;

    return font;
}


void xsChangeFont(xsFont* font, const char *path_to_ttf) {
    TTF_CloseFont((TTF_Font*)font->font);
    font->font = (xsBasicFont*)TTF_OpenFont(path_to_ttf, font->size);
}

char xsDrawFont(xsFont *font, const char *text, xsVec2i position) {
    SDL_Surface* text_surf;
    switch (font->draw_mode) {
        case XSUI_FONT_SOLID:
            text_surf = TTF_RenderUTF8_Solid(
                    (TTF_Font*)font->font, text,
                    (SDL_Color){font->text_color.r, font->text_color.g, font->text_color.b, font->text_color.a}
            );
            break;
        case XSUI_FONT_SHADED:
            text_surf = TTF_RenderUTF8_Shaded(
                    (TTF_Font*)font->font, text,
                    (SDL_Color){font->text_color.r, font->text_color.g, font->text_color.b, font->text_color.a},
                    (SDL_Color){font->bg_color.r, font->bg_color.g, font->bg_color.b, font->bg_color.a}
            );
            break;
        case XSUI_FONT_BLENDED:
            text_surf = TTF_RenderUTF8_Blended(
                    (TTF_Font*)font->font, text,
                    (SDL_Color){font->text_color.r, font->text_color.g, font->text_color.b, font->text_color.a}
            );
            break;
    }
    if (text_surf == NULL) {
        printf("ERROR: failed create text surface from this text %s err: %s", text, SDL_GetError());
        return 1;
    }

    SDL_Texture *text_tex = SDL_CreateTextureFromSurface(font->core->renderer, text_surf);
    if (text_tex == NULL) {
        printf("ERROR: failed convert text surf to texture err: %s", SDL_GetError());
        SDL_FreeSurface(text_surf);
        return 1;
    }


    SDL_Rect dest_rect = {position.x, position.y, text_surf->w, text_surf->h};
    SDL_RenderCopy(font->core->renderer, text_tex, NULL, &dest_rect);

    SDL_FreeSurface(text_surf);
    SDL_DestroyTexture(text_tex);
    return 0;
}

void xsFreeFont(xsFont *font) {
    if (font != NULL) {
        TTF_CloseFont((TTF_Font *) font->font);
        free(font);
    }
}

