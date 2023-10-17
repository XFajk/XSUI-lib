//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#include <xsUtils.h>
#include <xsCore.h>
#include <xsTypes.h>

#include <SDL.h>

void xsSetBackgroundColor(xsBasicImage *img, xsColor color) {
    unsigned int fill_color = SDL_MapRGBA(img->format, color.r, color.g, color.b, color.a);
    SDL_FillRect(img, NULL, fill_color);
}

void xsDrawRect(xsBasicImage *img, xsRect rect, xsColor color) {
    unsigned int fill_color = SDL_MapRGBA(img->format, color.r, color.g, color.b, color.a);
    SDL_Rect sdl_rect = {rect.x, rect.y, rect.w, rect.h};
    SDL_FillRect(img, &sdl_rect, fill_color);
}