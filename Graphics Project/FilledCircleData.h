#pragma once
#include "ShapeData.h"

class FilledCircleData:public ShapeData {
public:
    int xc,yc,x,y,q;
    FilledCircleData(int,int,int,int,COLORREF);
};
