#pragma once
#include "ShapeData.h"
#include "ShapeDrawer.h"

class CardinalSplineDrawer: public ShapeDrawer
{
public:
    void draw(ShapeData*);
};