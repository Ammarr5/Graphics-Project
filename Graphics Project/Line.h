#pragma once
#include "Shape.h"
#include "LineDrawer.h"
class Line: public Shape
{
public:
	Line(int, int, int, int, LineDrawer*);
};

