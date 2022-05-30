//
// Created by abdal on 5/29/2022.
//

#include "Point.h"
#include "PointDrawer.h"

Point::Point(PointData* data): Shape(data, new PointDrawer()) {
    draw();
}