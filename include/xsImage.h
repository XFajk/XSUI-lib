//
// Created by Rudolf Vrbenský on 15/10/2023.
//

#ifndef XSUILIB_XSIMAGE_H
#define XSUILIB_XSIMAGE_H

#include <xsCore.h>
#include <xsTypes.h>

typedef struct SDL_Surface xsBasicImage;

typedef struct xsImage {

    xsCore* core;

    xsBasicImage* image;
    int w;
    int h;

    xsColor color_key;

} xsImage;

xsImage* xsCreateImage(xsCore* core, int w, int h, xsColor color_key);
xsImage* xsLoadImage(xsCore* core, xsColor color_key, const char* path);

void xsDrawImage(xsImage* image, xsVec2f pos);
void xsDrawImageTransformed(xsImage* image, xsVec2f pos, xsVec2f new_size, float angle);

void xsDrawImageTo(xsImage* image, xsVec2f pos, xsImage* target);
void xsDrawImageTransformedTo(xsImage* image, xsVec2f pos, xsVec2f new_size, float angle, xsImage* target);

xsImage* xsGetImage(xsImage* image, xsVec2f pos);
xsImage* xsGetImageTransformed(xsImage* image, xsVec2f pos, xsVec2f new_size, float angle);

void xsFreeImage(xsImage* image);

#endif //XSUILIB_XSIMAGE_H
