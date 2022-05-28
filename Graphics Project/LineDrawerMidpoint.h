#pragma once
#include "ShapeData.h"
#include "LineDrawer.h"
class LineDrawerMidpoint: public LineDrawer
{
public:
    void draw(ShapeData*);
};

