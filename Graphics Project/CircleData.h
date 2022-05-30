#pragma once

#include <Windows.h>
#include "ShapeData.h"

class CircleData : public ShapeData{
public:
    int x1, y1, x2, y2;
public:
    CircleData(int, int, int, int, COLORREF);

};

