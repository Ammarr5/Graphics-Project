#pragma once
#include "Shape.h"
#include "EllipseDrawer.h"

class Ellipse : public Shape {
    ostream& format(ostream &out, const Shape &c);

public:
    Ellipse(int, int, int, int, int, int, COLORREF color, EllipseDrawer*);
};
