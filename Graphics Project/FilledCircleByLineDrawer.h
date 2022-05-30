#pragma once
#include "ShapeData.h"
#include "FilledCircleDrawer.h"
class FilledCircleByLineDrawer:public FilledCircleDrawer {
public:
    void draw(ShapeData*);
    void fill(ShapeData*);
};
