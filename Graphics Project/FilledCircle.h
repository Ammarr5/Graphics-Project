#pragma once
#include "Shape.h"
#include "FilledCircleDrawer.h"
class FilledCircle:public Shape {
public:
    FilledCircle(int, int, int, int, COLORREF color, FilledCircleDrawer*);
};
