//
// Created by abdal on 5/30/2022.
//

#ifndef GRAPHICS_PROJECT_POLYGONDATA_H
#define GRAPHICS_PROJECT_POLYGONDATA_H


#include "ShapeData.h"
#include "vector"
#include "PointData.h"

class PolygonData : public ShapeData{
public:
    std::vector<PointData*> points;
    PolygonData(std::vector<PointData*>, COLORREF);
};


#endif //GRAPHICS_PROJECT_POLYGONDATA_H
