#pragma once
#include "ShapeData.h"
#include "FilledCircleDrawer.h"
class FilledCircleByCircleDrawer:public FilledCircleDrawer {
    void draw(ShapeData*);
    void fill(ShapeData*);
};
