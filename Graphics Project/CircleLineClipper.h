//
// Created by Zeyad on 5/31/2022.
//

#ifndef GRAPHICS_PROJECT_CIRCLELINECLIPPER_H
#define GRAPHICS_PROJECT_CIRCLELINECLIPPER_H

#include "Clipper.h"
#include "LineData.h"
#include "CircleDrawer.h"

class CircleLineClipper: public Clipper{
public:
    CircleLineClipper(int xc, int yc, int x, int y, COLORREF,CircleDrawer*);
    bool clip(ShapeData*, Shape*&);
};


#endif //GRAPHICS_PROJECT_CIRCLELINECLIPPER_H
