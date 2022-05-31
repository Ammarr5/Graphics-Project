#pragma once
#include <Windows.h>

class FloodFill {
public:
    struct Color{
        float red, green, blue;
    };
    static void FloodFillNormal(int, int, COLORREF, COLORREF);
    static void FloodFillRecursive(int, int, Color, Color);
};
