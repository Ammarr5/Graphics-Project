#pragma once
#include "ShapeData.h"
#include "LineDrawer.h"
class LineDrawerParametric: public LineDrawer
{
public:
    void draw(ShapeData*);
};