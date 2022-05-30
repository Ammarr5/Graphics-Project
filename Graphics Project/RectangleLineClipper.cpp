//
// Created by abdal on 5/29/2022.
//

#include "RectangleLineClipper.h"
#include "Rectangle.h"
#include "RectangleData.h"
#include "Line.h"
#include "LineDrawerDDA.h"
#include "cmath"

RectangleLineClipper::RectangleLineClipper(int xt, int yt, int xb, int yb, COLORREF color) {
    this->windowShape = new class Rectangle(xt, yt, xb, yb, color);
}

bool RectangleLineClipper::clip(ShapeData* data, Shape*& clipped) {
    RectangleData window = *(RectangleData*)this->windowShape->shapeData;
    LineData ld = *(LineData*) data;
    outcode outCode1 = getOutCode(ld.x1, ld.y1);
    outcode outCode2 = getOutCode(ld.x2, ld.y2);
    while (true) {
        if (outCode1.all & outCode2.all) {
            clipped = nullptr;
            return false;
        }
        if(!outCode1.all && !outCode2.all) {
            clipped = new Line(ld.x1, ld.y1, ld.x2, ld.y2, ld.color, new LineDrawerDDA());
            return true;
        }
        if (outCode1.all) {
            if(outCode1.left) {
                getVIntersection(ld.x1, ld.y1, ld.x2, ld.y2, window.xt, ld.x1, ld.y1);
            }
            else if(outCode1.right) {
                getVIntersection(ld.x1, ld.y1, ld.x2, ld.y2, window.xb, ld.x1, ld.y1);
            }
            else if(outCode1.top) {
                getHIntersection(ld.x1, ld.y1, ld.x2, ld.y2, window.yt, ld.x1, ld.y1);
            }
            else if (outCode1.bottom) {
                getHIntersection(ld.x1, ld.y1, ld.x2, ld.y2, window.yb, ld.x1, ld.y1);
            }
            outCode1 = getOutCode(ld.x1, ld.y1);
        }
        else if (outCode2.all) {
            if(outCode2.left) {
                getVIntersection(ld.x1, ld.y1, ld.x2, ld.y2, window.xt, ld.x2, ld.y2);
            }
            else if(outCode2.right) {
                getVIntersection(ld.x1, ld.y1, ld.x2, ld.y2, window.xb, ld.x2, ld.y2);
            }
            else if(outCode2.top) {
                getHIntersection(ld.x1, ld.y1, ld.x2, ld.y2, window.yt, ld.x2, ld.y2);
            }
            else if (outCode2.bottom) {
                getHIntersection(ld.x1, ld.y1, ld.x2, ld.y2, window.yb, ld.x2, ld.y2);
            }
            outCode2 = getOutCode(ld.x2, ld.y2);
        }
    }
}

outcode RectangleLineClipper::getOutCode(int x, int y) {
    RectangleData window = *(RectangleData*)this->windowShape->shapeData;
    outcode outCode;
    outCode.all = 0;
    if(x < window.xt) {
        outCode.left = 1;
    }
    else if(x > window.xb) {
        outCode.right = 1;
    }
    if(y < window.yt) {
        outCode.top = 1;
    }
    else if (y > window.yb) {
        outCode.bottom = 1;
    }
    return outCode;
}

void RectangleLineClipper::getVIntersection(int x1, int y1, int x2, int y2, int xl, int& xr, int& yr) { // xl is x of the line to intesect with
    int yTemp = ceil((double)y1 + (double)((y2 - y1)*(xl - x1)/(double)(x2 - x1)));
    xr = xl;
    yr = yTemp;
}

void RectangleLineClipper::getHIntersection(int x1, int y1, int x2, int y2, int yl, int& xr, int& yr) { // yl is y of the line to intesect with
//    int xTemp = x1 + ((yl - y1)*(x2 - x1))/(y2 - y1);
    int xTemp = x1 + (yl - y1)*(x2 - x1)/(y2 - y1);
    yr = yl;
    xr = xTemp;
    int i;
}

