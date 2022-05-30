//
// Created by abdal on 5/29/2022.
//

#ifndef GRAPHICS_PROJECT_RECTANGLEPOINTCLIPPER_H
#define GRAPHICS_PROJECT_RECTANGLEPOINTCLIPPER_H


#include "Clipper.h"

class RectanglePointClipper : public Clipper{
public:
    RectanglePointClipper(int xt, int yt, int xb, int yb, COLORREF);
    bool clip(ShapeData*, Shape*);
};


#endif //GRAPHICS_PROJECT_RECTANGLEPOINTCLIPPER_H
