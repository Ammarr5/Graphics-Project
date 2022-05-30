//
// Created by abdal on 5/29/2022.
//

#ifndef GRAPHICS_PROJECT_CLIPPER_H
#define GRAPHICS_PROJECT_CLIPPER_H

#include "Shape.h"

class Clipper {
public:
    Shape* windowShape;
    Shape* getShape() {
        return windowShape;
    }

    virtual bool clip(ShapeData*, Shape*&) = 0;
};


#endif //GRAPHICS_PROJECT_CLIPPER_H
