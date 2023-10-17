//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#ifndef XSUILIB_XSUTILS_H
#define XSUILIB_XSUTILS_H

typedef struct xsCore xsCore;
typedef struct xsRect xsRect;
typedef struct xsColor xsColor;
typedef struct SDL_Surface xsBasicImage;

void xsSetBackgroundColor(xsBasicImage *img, xsColor color);
void xsDrawRect(xsBasicImage *img, xsRect rect, xsColor color);

#endif // XSUILIB_XSUTILS_H