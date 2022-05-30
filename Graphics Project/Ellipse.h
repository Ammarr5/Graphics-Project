#pragma once
#include "Shape.h"
#include "EllipseDrawer.h"

class Ellipse : public Shape {

public:
    Ellipse(int, int, int, int, int, int, COLORREF color, EllipseDrawer*);
};
