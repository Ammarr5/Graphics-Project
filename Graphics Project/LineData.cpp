#include "LineData.h"
LineData::LineData(int x1, int y1, int x2, int y2, COLORREF color) {
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
    this->color = color;
}