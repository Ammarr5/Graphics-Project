//
// Created by abdal on 5/29/2022.
//

#ifndef GRAPHICS_PROJECT_RECTANGLELINECLIPPER_H
#define GRAPHICS_PROJECT_RECTANGLELINECLIPPER_H


#include "Clipper.h"
#include "LineData.h"

union outcode {
    unsigned int all: 4;
    struct {
        unsigned int left: 1;
        unsigned int right: 1;
        unsigned int top: 1;
        unsigned int bottom: 1;
    };
};

class RectangleLineClipper: public Clipper{
public:
    RectangleLineClipper(int xt, int yt, int xb, int yb, COLORREF);
    bool clip(ShapeData*, Shape*&);
    outcode getOutCode(int, int);
    static void getVIntersection(int, int, int, int, int, int&, int&);
    static void getHIntersection(int, int, int, int, int, int&, int&);
};


#endif //GRAPHICS_PROJECT_RECTANGLELINECLIPPER_H
