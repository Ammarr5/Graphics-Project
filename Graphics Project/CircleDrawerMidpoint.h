#pragma once
#include "ShapeData.h"
#include "CircleDrawer.h"
class CircleDrawerMidpoint: public CircleDrawer{
public:
    void draw(ShapeData*) override;
};
