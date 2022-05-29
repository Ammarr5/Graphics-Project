#include "CardinalSplineData.h"
CardinalSplineData::CardinalSplineData(Vector& points,int n,double c, COLORREF color){
    this->points = &points;
    this->n = n;
    this->c = c;
    this->color = color;
}