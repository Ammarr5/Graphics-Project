//
// Created by Zeyad on 5/31/2022.
//

#include "CircleLineClipper.h"
#include "Circle.h"
#include "CircleData.h"
#include "Line.h"
#include "CircleDrawerDirect.h"
#include "PointData.h"
#include "Point.h"

CircleLineClipper::CircleLineClipper(int xc, int yc, int x, int y, COLORREF color,CircleDrawer* drawer) {
    this->windowShape = new class Circle(xc, yc, x, y, color,drawer);
}

double getRadius(int xc, int yc, int x, int y) {
    return sqrt((x - xc) * (x - xc) + (y - yc) * (y - yc));
}

bool CircleLineClipper::clip(ShapeData* shapeData, Shape*& clipped) {
    CircleData window = *(CircleData*)windowShape->shapeData;
    double radius= getRadius(window.x1,window.y1,window.x2,window.y2);
    cout<<"Line Parametric algorithm selected."<<endl;
    LineData lData = *(LineData *) shapeData;
    int x1 = lData.x1;
    int y1 = lData.y1;
    int x2 = lData.x2;
    int y2 = lData.y2;
    COLORREF color = lData.color;

    for (double t = 0; t <= 1; t += 0.001) {
        int x = x1 + (x2 - x1) * t;
        int y = y1 + (y2 - y1) * t;
        double d = (round(x) - window.x1) * (round(x) - window.x1) + (round(y) - window.y1) * (round(y) - window.y1) - radius * radius;
        if(d<0) {
            PointData *pData = new PointData(x,y,color);
            clipped = new Point(pData);
        }
        clipped = nullptr;
    }
}

