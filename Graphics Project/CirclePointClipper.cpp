//
// Created by Zeyad on 5/31/2022.
//

#include "CirclePointClipper.h"
#include "Circle.h"
#include "CircleData.h"
#include "Point.h"

CirclePointClipper::CirclePointClipper(int xc, int yc, int x, int y, COLORREF color, CircleDrawer* drawer) {
    this->windowShape = new class Circle(xc, yc, x, y, color,drawer);
}

double calculateRadius(int xc, int yc, int x, int y) {
    return sqrt((x - xc) * (x - xc) + (y - yc) * (y - yc));
}

bool CirclePointClipper::clip(ShapeData* shapeData, Shape*& clipped) {
    PointData p = *(PointData*) shapeData;
    CircleData window = *(CircleData*)windowShape->shapeData;
    double radius= calculateRadius(window.x1,window.y1,window.x2,window.y2);
    double d = (round(p.x) - window.x1) * (round(p.x) - window.x1) + (round(p.y) - window.y1) * (round(p.y) - window.y1) - radius * radius;
    if(d<0) {
        clipped = new Point(&p);
        return true;
    }
    clipped = nullptr;
    return false;
}
