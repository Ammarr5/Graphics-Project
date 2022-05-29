#pragma once
#include <Windows.h>
#include "ShapeData.h"

class Vector {
    double v[2];
public:
    Vector(double x = 0, double y = 0)
    {
        v[0] = x;
        v[1] = y;
    }
    double& operator[](int i) {
        return v[i];
    }
};

class CardinalSplineData: public ShapeData
{
public:
    int n;
    Vector* points;
    double c;
    COLORREF color;
public:
    CardinalSplineData(Vector&,int,double, COLORREF);
};
