//
// Created by Rudolf Vrbenský on 24/09/2023.
//

#ifndef XSUILIB_XSUI_H
#define XSUILIB_XSUI_H

#include <stdio.h>
#include <SDL.h>

#include <xsCore.h>

char xsInitCore(xsCore *core, const char* win_title, int* win_pos, int* win_size, Uint32 win_flags);

#endif //XSUILIB_XSUI_H
