#pragma once
#include "ShapeDrawer.h"
#include "LineData.h"
class LineDrawer: public ShapeDrawer
{
public:
	virtual void draw(ShapeData*) = 0;


    void swap(int& x1, int& y1, int& x2, int& y2)
    {
        int tmp = x1;
        x1 = x2;
        x2 = tmp;
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    int Round(double x)
    {
        return (int)(x + 0.5);
    }
};

