#pragma once
#include "ShapeData.h"
#include "CircleDrawer.h"

class CircleDrawerPolar: public CircleDrawer{
public:
    void draw(ShapeData*) override;
};

