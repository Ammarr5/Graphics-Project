#pragma once
#include "Shape.h"
#include "CircleDrawer.h"


class Circle : public Shape
{
    Circle(int, int, int, int,COLORREF color, CircleDrawer*);
};


