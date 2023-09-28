//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#ifndef XSUILIB_XSTYPES_H
#define XSUILIB_XSTYPES_H

typedef struct xsVec2f {
    float x;
    float y;
} xsVec2f;


typedef struct xsVec2i {
    int x;
    int y;
} xsVec2i;

typedef struct xsColor {
    int r;
    int g;
    int b;
    int a;
} xsColor;

typedef struct xsRect {
    int x;
    int y;
    int w;
    int h;
} xsRect;

#endif //XSUILIB_XSTYPES_H