//
// Created by abdal on 5/29/2022.
//

#include "Rectangle.h"
#include "RectangleData.h"
#include "RectangleDrawer.h"

Rectangle::Rectangle(int xt, int yt, int xb, int yb, COLORREF color): Shape(new RectangleData(xt, yt, xb, yb, color), new RectangleDrawer()) {
    draw();
}