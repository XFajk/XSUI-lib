//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#include <xsUtils.h>
#include <xsCore.h>
#include <xsTypes.h>

#include <SDL.h>

void xsSetBackgroundColor(xsCore *core, xsColor color) {
    unsigned int fill_color = SDL_MapRGBA(core->display->format, color.r, color.g, color.b, color.a);
    SDL_FillRect(core->display, NULL, fill_color);
}

void xsDrawRect(xsCore *core, xsRect rect, xsColor color) {
    unsigned int fill_color = SDL_MapRGBA(core->display->format, color.r, color.g, color.b, color.a);
    SDL_Rect sdl_rect = {rect.x, rect.y, rect.w, rect.h};
    SDL_FillRect(core->display, &sdl_rect, fill_color);
}