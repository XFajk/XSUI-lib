//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#ifndef XSUILIB_XSCORE_H
#define XSUILIB_XSCORE_H

#include <SDL.h>

typedef struct xsCore {

    SDL_Window *window;
    SDL_Renderer *renderer;
    char exit_flag;

};

#endif // XSUILIB_XSCORE_H