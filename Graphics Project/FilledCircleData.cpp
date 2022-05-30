#include "FilledCircleData.h"
FilledCircleData::FilledCircleData(int xc, int yc, int x, int y, COLORREF color) {
    this->xc=xc;
    this->yc=yc;
    this->x=x;
    this->y=y;
    this->q=0;
    this->color = color;
}