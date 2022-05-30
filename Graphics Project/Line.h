#pragma once
#include "Shape.h"
#include "LineDrawer.h"
class Line: public Shape
{
public:
	Line(int, int, int, int,COLORREF color, LineDrawer*);
    ostream& format(ostream &out, const Shape &c);
};

