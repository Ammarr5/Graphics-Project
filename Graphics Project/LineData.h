#pragma once

#include <Windows.h>
#include "ShapeData.h"
class LineData: public ShapeData
{
public:
	int x1, y1, x2, y2;
public:
	LineData(int, int, int, int, COLORREF);
};

