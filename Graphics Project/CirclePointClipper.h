//
// Created by Zeyad on 5/31/2022.
//

#ifndef GRAPHICS_PROJECT_CIRCLEPOINTCLIPPER_H
#define GRAPHICS_PROJECT_CIRCLEPOINTCLIPPER_H

#include "Clipper.h"
#include "CircleDrawer.h"

class CirclePointClipper:public Clipper {
public:
    CirclePointClipper(int xt, int yt, int xb, int yb, COLORREF,CircleDrawer*);
    bool clip(ShapeData*, Shape*&);
};


#endif //GRAPHICS_PROJECT_CIRCLEPOINTCLIPPER_H
