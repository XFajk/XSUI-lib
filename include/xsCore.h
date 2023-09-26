//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#ifndef XSUILIB_XSCORE_H
#define XSUILIB_XSCORE_H

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

typedef union SDL_Event xsEvent;

typedef struct Vec2 Vec2;

typedef struct xsCore {

    SDL_Window *window;
    SDL_Renderer *renderer;
    char exit_flag;

} xsCore;

char xsInitCore(xsCore *core, const char* win_title, Vec2 win_pos, Vec2 win_size, unsigned int win_flags);

char xsRunCore(xsCore *core, void (*game_loop)(xsCore *core, xsEvent *event));
void xsUpdateCoreState(xsCore* core);

void xsFreeCore(xsCore *core);

void xsBasicGameLoop(xsCore *core, xsEvent *event);

#endif // XSUILIB_XSCORE_H