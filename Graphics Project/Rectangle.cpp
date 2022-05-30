//
// Created by abdal on 5/29/2022.
//

#include "Rectangle.h"
#include "RectangleData.h"
#include "RectangleDrawer.h"

Rectangle::Rectangle(int xt, int yt, int xb, int yb, COLORREF color): Shape(new RectangleData(xt, yt, xb, yb, color), new RectangleDrawer()) {
    draw();
}

ostream& Rectangle::format(ostream &out, const Shape &c) {
    RectangleData data = *(RectangleData*) shapeData;
    out<<"rectangle "<<data.xt<<" "<<data.yt<<" "<<data.xb<<" "<<data.yb<<" - "<<((int)GetRValue(data.color))<<" "<<((int)GetGValue(data.color))<<" "<<((int)GetBValue(data.color));
    return out;
}