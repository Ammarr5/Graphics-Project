#include "EllipseData.h"

EllipseData::EllipseData(int x1, int y1, int x2, int y2, int x3, int y3, COLORREF color) : ShapeData()
{
    this->x1 = x1;
    this->x2 = x2;
    this->x3 = x3;
    this->y1 = y1;
    this->y2 = y2;
    this->y3 = y3;
    this->color = color;
}