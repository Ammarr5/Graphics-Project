//
// Created by abdal on 5/29/2022.
//

#include "Point.h"
#include "PointDrawer.h"

Point::Point(PointData* data): Shape(data, new PointDrawer()) {
    draw();
}

ostream& Point::format(ostream &out, const Shape &c) {
    PointData data = *(PointData*) shapeData;
    out<<"point "<<data.x<<" "<<data.y<<" - "<<((int)GetRValue(data.color))<<" "<<((int)GetGValue(data.color))<<" "<<((int)GetBValue(data.color));
    return out;
}