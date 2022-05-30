#pragma once
#include <Windows.h>

class FloodFill {
public:
    static void FloodFillNormal(int, int, COLORREF, COLORREF);
    static void FloodFillRecursive(int, int, COLORREF, COLORREF);
};
