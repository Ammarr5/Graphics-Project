#include "CircleData.h"

CircleData::CircleData(int x1, int y1, int x2, int y2, COLORREF color) : ShapeData()
{
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
    this->color = color;
}