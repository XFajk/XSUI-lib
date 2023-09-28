//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#include <xsUtils.h>
#include <xsCore.h>
#include <xsTypes.h>

#include <SDL.h>

void xsDrawRect(xsCore *core, xsRect rect, xsColor color) {
    SDL_SetRenderDrawColor(core->renderer, color.r, color.g, color.b, color.a);
    SDL_Rect sdl_rect = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderDrawRect(core->renderer, &sdl_rect);
}