#pragma once
#include "Shape.h"
#include "EllipseDrawer.h"

class Ellipse : public Shape {
    Ellipse(int, int, int, int, int, int, COLORREF color, EllipseDrawer*);

};
