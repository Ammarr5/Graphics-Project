//
// Created by abdal on 5/29/2022.
//

#ifndef GRAPHICS_PROJECT_POINT_H
#define GRAPHICS_PROJECT_POINT_H


#include "Shape.h"
#include "PointData.h"

class Point: public Shape {
public:
    Point(PointData*);
    ostream& format(ostream &out, const Shape &c);
};


#endif //GRAPHICS_PROJECT_POINT_H
