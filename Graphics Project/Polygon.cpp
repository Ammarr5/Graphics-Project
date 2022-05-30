//
// Created by abdal on 5/30/2022.
//

#include "Polygon.h"
#include "PolygonData.h"
#include "PolygonDrawer.h"

Polygon::Polygon(std::vector<PointData*> points, COLORREF color): Shape(new PolygonData(points, color), new PolygonDrawer()) {
    draw();
}

ostream& Polygon::format(ostream &out, const Shape &c) {
    PolygonData data = *(PolygonData*) shapeData;
    out<<"polygon";
    for(int i=0; i<data.points.size(); i++) {
        PointData* point = data.points.at(i);
        out<<" "<<point->x<<" "<<point->y;
    }
    out<<" - "<<((int)GetRValue(data.color))<<" "<<((int)GetGValue(data.color))<<" "<<((int)GetBValue(data.color));
    return out;
}