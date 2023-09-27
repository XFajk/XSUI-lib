//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#ifndef XSUILIB_XSCORE_H
#define XSUILIB_XSCORE_H

typedef struct SDL_Window xsWindow;
typedef struct SDL_Renderer xsRenderer;

typedef union SDL_Event xsEvent;

typedef struct Vec2i Vec2i;

typedef struct xsCore {

    xsWindow *window;
    xsRenderer *renderer;
    char exit_flag;
    xsEvent* event;

} xsCore;

int xsInitCore(xsCore *core, const char* win_title, Vec2i win_pos, Vec2i win_size, unsigned int win_flags);

void xsUpdateCoreEvents(xsCore* core);
void xsUpdateCoreState(xsCore* core);

int xsEventQuitCore(xsCore* core);

void xsFreeCore(xsCore *core);

void xsBasicAppLoop(xsCore *core);

#endif // XSUILIB_XSCORE_H