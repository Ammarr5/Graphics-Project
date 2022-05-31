#pragma once
#include <Windows.h>

class FloodFill {
public:
    FloodFill();
    void FloodFillNormal(HDC, int, int, COLORREF, COLORREF);
    void FloodFillRecursive(HDC, int, int, COLORREF, COLORREF);
};
