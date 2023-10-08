//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#ifndef XSUILIB_XSCORE_H
#define XSUILIB_XSCORE_H

#include <xsTypes.h>

typedef struct SDL_Window xsWindow;
typedef struct SDL_Renderer xsRenderer;

typedef union SDL_Event xsEvent;

typedef struct xsCore {

    xsWindow *window;
    xsRenderer *renderer;
    char exit_flag;

    unsigned long _last_time;
    float frame_time;

    xsEvent* event;
    const unsigned char *keyboard_state;
    int number_of_keys;
    unsigned int mouse_state;
    xsVec2i mouse_pos;

} xsCore;

char xsInitCore(xsCore *core, const char* win_title, xsVec2i win_pos, xsVec2i win_size, unsigned int win_flags);

void xsUpdateCoreRendering(xsCore* core);
void xsUpdateCoreState(xsCore* core);

char xsEventQuitCore(xsCore* core);

void xsFreeCore(xsCore *core);

#endif // XSUILIB_XSCORE_H