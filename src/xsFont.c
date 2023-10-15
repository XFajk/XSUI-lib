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

    font->_path = path_to_ttf;

    printf("INFO: the xsFont was created successfully\n");
    return font;
}


void xsChangeFont(xsFont* font, const char *path_to_ttf) {
    TTF_CloseFont((TTF_Font*)font->font);
    font->font = (xsBasicFont*)TTF_OpenFont(path_to_ttf, font->size);
}

char xsDrawFont(xsFont *font, const char *text, xsVec2f position) {
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


    SDL_Rect dest_rect = {(int)position.x-text_surf->w/2, (int)position.y-text_surf->h/2, text_surf->w, text_surf->h};
    SDL_BlitSurface(text_surf, NULL, font->core->display, &dest_rect);

    SDL_FreeSurface(text_surf);
    return 0;
}

char xsDrawFontScaled(xsFont *font, const char *text, xsVec2f position, xsVec2f size) {
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


    SDL_Rect dest_rect = {(int)(position.x-size.x), (int)(position.y-size.y), (int)size.x*2.f, (int)size.y*2.f};
    SDL_BlitScaled(text_surf, NULL, font->core->display, &dest_rect);

    SDL_FreeSurface(text_surf);
    return 0;
}

char xsFontGetTextImage(xsFont *font, const char *text) {
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

    SDL_FreeSurface(text_surf);
    return 0;
}

void xsFreeFont(xsFont *font) {
    if (font != NULL) {
        TTF_CloseFont((TTF_Font *) font->font);
        free(font);
    }
}

xsFont* xsCopyFont(xsFont *font) {
    xsFont *copy_font = xsCreateFont(font->core, font->_path, font->size, font->text_color, font->draw_mode);
    if (copy_font == NULL) {
        printf("ERROR: failed to initialize the buttons font\n");
        return NULL;
    }
    copy_font->bg_color = font->bg_color;

    return copy_font;
}

