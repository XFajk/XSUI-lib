// 
// Created by Rudolf Vrbenský on 24/09/2023.
// 
#ifndef XSUILIB_XSMATH_H
#define XSUILIB_XSMATH_H

#include <math.h>

typedef struct Vec2 {
    float x;
    float y;
};

int* Vec2ToInt(Vec2 vec);

#endif // XSUILIB_XSMATH_H