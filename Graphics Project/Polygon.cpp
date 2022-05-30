//
// Created by abdal on 5/30/2022.
//

#include "Polygon.h"
#include "PolygonData.h"
#include "PolygonDrawer.h"

Polygon::Polygon(std::vector<PointData*> points, COLORREF color): Shape(new PolygonData(points, color), new PolygonDrawer()) {
    draw();
}
