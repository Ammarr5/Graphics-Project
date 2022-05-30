//
// Created by abdal on 5/30/2022.
//

#ifndef GRAPHICS_PROJECT_RECTANGLEPOLYGONCLIPPER_H
#define GRAPHICS_PROJECT_RECTANGLEPOLYGONCLIPPER_H


#include "Clipper.h"
#include "PolygonData.h"

class RectanglePolygonClipper: public Clipper{
public:
    RectanglePolygonClipper(int xt, int yt, int xb, int yb, COLORREF);
    bool clip(ShapeData*, Shape*&);
    void clipLeft(PolygonData&, int);
    void clipRight(PolygonData&, int);
    void clipTop(PolygonData&, int);
    void clipBottom(PolygonData&, int);
};


#endif //GRAPHICS_PROJECT_RECTANGLEPOLYGONCLIPPER_H
