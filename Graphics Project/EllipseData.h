#pragma once

#include <Windows.h>
#include "ShapeData.h"

class EllipseData : public ShapeData{
public:
    int x1, y1, x2, y2, x3, y3;
public:
    EllipseData(int, int, int, int, int, int, COLORREF);

};

