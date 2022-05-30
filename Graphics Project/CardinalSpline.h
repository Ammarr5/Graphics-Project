#pragma once
#include "Shape.h"
#include "CardinalSplineDrawer.h"
#include "CardinalSplineData.h"

class CardinalSpline:public Shape {
public:
    CardinalSpline(Vector *points, int, double, COLORREF color, CardinalSplineDrawer*);
    ostream& format(ostream &out, const Shape &c);
};
