// 
// Created by Rudolf Vrbenský on 24/09/2023.
// 

#include <xsMath.h>

int* Vec2ToInt(Vec2 vec) {
    int[2] result;

    result[0] = (int)floor(vec.x);
    result[1] = (int)floor(vec.y);
    
    return result;
}