//
// Created by Rudolf Vrbenský on 27/09/2023.
//

#ifndef XSUILIB_XSUTILS_H
#define XSUILIB_XSUTILS_H

typedef struct xsCore xsCore;
typedef struct xsRect xsRect;
typedef struct xsColor xsColor;

void xsSetBackgroundColor(xsCore *core, xsColor color);
void xsDrawRect(xsCore *core, xsRect rect, xsColor color);

#endif // XSUILIB_XSUTILS_H