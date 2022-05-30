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
};


#endif //GRAPHICS_PROJECT_POLYGON_H
