//
// Created by abdal on 5/30/2022.
//

#ifndef GRAPHICS_PROJECT_POLYGON_H
#define GRAPHICS_PROJECT_POLYGON_H


#include <vector>
#include "Shape.h"
#include "PolygonData.h"
#include "PointData.h"

class Polygon: public Shape{
public:
    Polygon(std::vector<PointData*>, COLORREF);
    ostream& format(ostream &out, const Shape &c);
};


#endif //GRAPHICS_PROJECT_POLYGON_H
