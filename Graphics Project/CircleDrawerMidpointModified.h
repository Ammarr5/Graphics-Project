#pragma once
#include "ShapeData.h"
#include "CircleDrawer.h"
class CircleDrawerMidpointModified: public CircleDrawer{
public:
    void draw(ShapeData*) override;
};

