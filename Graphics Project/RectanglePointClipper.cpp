//
// Created by abdal on 5/29/2022.
//

#include "RectanglePointClipper.h"
#include "Rectangle.h"
#include "RectangleData.h"
#include "Point.h"

RectanglePointClipper::RectanglePointClipper(int xt, int yt, int xb, int yb, COLORREF color) {
    this->windowShape = new class Rectangle(xt, yt, xb, yb, color);
}

bool RectanglePointClipper::clip(ShapeData* shapeData, Shape* clipped) {
    PointData p = *(PointData*) shapeData;
    RectangleData window = *(RectangleData*)windowShape->shapeData;
    if(p.x >= window.xt && p.x <= window.xb && p.y >= window.yt && p.y <= window.yb) {
        clipped = new Point(&p);
        return true;
    }
    clipped = nullptr;
    return false;
}