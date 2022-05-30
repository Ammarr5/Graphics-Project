#pragma once
#include "ShapeDrawer.h"
#include "FilledCircleData.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>
#include <math.h>

class FilledCircleDrawer:public ShapeDrawer {
public:
    virtual void draw(ShapeData*) = 0;
    virtual void fill(ShapeData*) = 0;
    void Draw8Points(int xc, int yc, int x, int y)
    {
        glVertex2d(xc + x, yc + y);
        glVertex2d(xc + x, yc - y);
        glVertex2d(xc - x, yc - y);
        glVertex2d(xc - x, yc + y);
        glVertex2d(xc + y, yc + x);
        glVertex2d(xc + y, yc - x);
        glVertex2d(xc - y, yc - x);
        glVertex2d(xc - y, yc + x);
    }
    double calculateRadius(int xc, int yc, int x, int y) {
        return sqrt((x - xc) * (x - xc) + (y - yc) * (y - yc));
    }
};
