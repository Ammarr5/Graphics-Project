//
// Created by abdal on 5/30/2022.
//

#include "PolygonData.h"
PolygonData::PolygonData(std::vector<PointData*> points, COLORREF color) {
    this->points = points;
    this->color = color;
}
