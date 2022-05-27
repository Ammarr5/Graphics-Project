#pragma once
#include "Shape.h"
#include "LineDrawer.h"
class Line: protected Shape
{
public:
	Line(int, int, int, int, LineDrawer*);
};

