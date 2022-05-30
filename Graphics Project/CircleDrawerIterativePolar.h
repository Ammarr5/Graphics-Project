#pragma once
#include "ShapeData.h"
#include "CircleDrawer.h"

class CircleDrawerIterativePolar: public CircleDrawer {
public:
    void draw(ShapeData*) override;
};
