//
// Created by abdal on 5/29/2022.
//

#ifndef GRAPHICS_PROJECT_POINTDATA_H
#define GRAPHICS_PROJECT_POINTDATA_H


#include "ShapeData.h"

class PointData: public ShapeData {
public:
    int x;
    int y;
    PointData(int x, int y, COLORREF color) {
        this->x = x;
        this->y = y;
        this->color = color;
    }
};


#endif //GRAPHICS_PROJECT_POINTDATA_H
