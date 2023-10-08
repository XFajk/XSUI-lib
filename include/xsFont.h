//
// Created by Rudolf Vrbenský on 07/10/2023.
//

#ifndef XSUILIB_XSFONT_H
#define XSUILIB_XSFONT_H

#include <xsTypes.h>
#include <xsCore.h>

typedef struct TTF_Font xsBasicFont;

typedef enum xsFontDrawMode {
    XSUI_FONT_SOLID,
    XSUI_FONT_SHADED,
    XSUI_FONT_BLENDED,
} xsFontDrawMode;

typedef struct xsFont {
    xsColor text_color;
    xsColor bg_color;
    int size;

    xsBasicFont* font;
    enum xsFontDrawMode draw_mode;

    xsCore *core;
} xsFont;

xsFont* xsCreateFont(xsCore *core, const char *path_to_ttf, int size, xsColor color, enum xsFontDrawMode mode);

void xsChangeFont(xsFont *font, const char* path_to_ttf);

char xsDrawFont(xsFont *font, const char *text, xsVec2i position);

void xsFreeFont(xsFont *font);

#endif //XSUILIB_XSFONT_H
