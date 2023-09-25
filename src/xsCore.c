//
// Created by Rudolf Vrbenský on 24/09/2023.
//


#include <xsCore.h>
#include <xsMath.h>

#include <SDL.h>
#include <stdio.h>


char xsInitCore(xsCore *core, const char* win_title, Vec2 win_pos, Vec2 win_size, Uint32 win_flags) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("INFO: SDL initialized successfully\n");
    } else {
        printf("ERROR: SDL failed to initialize: %s\n", SDL_GetError());
        return 1;
    }

    core->window = SDL_CreateWindow(
            win_title,
            win_pos.x, win_pos.y, win_size.x, win_size.y,
            win_flags
    );
    if (core->window != NULL)
    {
        printf("INFO: SDL created window successfully\n");
    } else {
        printf("ERROR: SDL failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    core->renderer = SDL_CreateRenderer(core->window, -1, SDL_RENDERER_SOFTWARE);
    if (core->renderer != NULL) {
        printf("INFO: SDL created renderer successfully\n");
    } else {
        printf("ERROR: SDL failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(core->window);
        SDL_Quit();
        return 1;
    }

    return 0;
}




void xsFreeCore(xsCore *core) {
    core->exit_flag = 1;
    SDL_DestroyRenderer(core->renderer);
    SDL_DestroyWindow(core->window);
    SDL_Quit();
}

