#pragma once
#include "ShapeDrawer.h"
#include "CircleData.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>
#include <cmath>
#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
class CircleDrawer : public ShapeDrawer{
public:
    void draw(ShapeData*) override = 0;

    static void Draw8Points(int xc, int yc, int x, int y)
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

};


