//
// Created by abdal on 5/29/2022.
//

#ifndef GRAPHICS_PROJECT_RECTANGLEDATA_H
#define GRAPHICS_PROJECT_RECTANGLEDATA_H


#include "ShapeData.h"

class RectangleData : public ShapeData {
public:
    int xt;
    int yt;
    int xb;
    int yb;
    RectangleData(int, int, int, int, COLORREF);
};


#endif //GRAPHICS_PROJECT_RECTANGLEDATA_H
