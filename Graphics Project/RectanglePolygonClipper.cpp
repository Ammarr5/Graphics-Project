//
// Created by abdal on 5/30/2022.
//

#include "RectanglePolygonClipper.h"
#include "Rectangle.h"
#include "PolygonData.h"
#include "RectangleLineClipper.h"
#include "RectangleData.h"
#include "Polygon.h"

RectanglePolygonClipper::RectanglePolygonClipper(int xt, int yt, int xb, int yb, COLORREF color) {
    this->windowShape = new class Rectangle(xt, yt, xb, yb, color);
}

bool RectanglePolygonClipper::clip(ShapeData* data, Shape* clipped) {
    PolygonData pd = *(PolygonData*) data;
    RectangleData window = *(RectangleData*)windowShape->shapeData;

    clipLeft(pd, window.xt);
    clipRight(pd, window.xb);
    clipTop(pd, window.yt);
    clipBottom(pd, window.yb);
    if (pd.points.empty()) {
        clipped = nullptr;
        return false;
    }
    clipped = new class Polygon(pd.points, pd.color);
}

void RectanglePolygonClipper::clipLeft(PolygonData& pd, int xl) {
    PointData* v1 = pd.points.at(0);
    std::vector<PointData*> outList;
    for (int i=1; i != 0; (i !=0 && i++)) {
        if (i == pd.points.size()){i = 0;}
        PointData* v2 = pd.points.at(i);
        if(v1->x >= xl && v2->x < xl) {
            int xTemp;
            int yTemp;
            RectangleLineClipper::getVIntersection(v1->x, v1->y, v2->x, v2->y, xl, xTemp, yTemp);
            outList.push_back(new PointData(xTemp, yTemp, pd.color));
        }
        else if(v1->x < xl && v2->x >= xl) {
            int xTemp;
            int yTemp;
            RectangleLineClipper::getVIntersection(v1->x, v1->y, v2->x, v2->y, xl, xTemp, yTemp);
            outList.push_back(new PointData(xTemp, yTemp, pd.color));
            outList.push_back(v2);
        }
        else if(v1->x >= xl && v2->x >= xl) {
            outList.push_back(v2);
        }
        v1 = v2;
    }
    pd.points = outList;
}
void RectanglePolygonClipper::clipRight(PolygonData& pd, int xr) {
    PointData* v1 = pd.points.at(0);
    std::vector<PointData*> outList;
    for (int i=1; i != 0; (i !=0 && i++)) {
        if (i == pd.points.size()){i = 0;}
        PointData* v2 = pd.points.at(i);
        if(v1->x <= xr && v2->x > xr) {
            int xTemp;
            int yTemp;
            RectangleLineClipper::getVIntersection(v1->x, v1->y, v2->x, v2->y, xr, xTemp, yTemp);
            outList.push_back(new PointData(xTemp, yTemp, pd.color));
        }
        else if(v1->x > xr && v2->x <= xr) {
            int xTemp;
            int yTemp;
            RectangleLineClipper::getVIntersection(v1->x, v1->y, v2->x, v2->y, xr, xTemp, yTemp);
            outList.push_back(new PointData(xTemp, yTemp, pd.color));
            outList.push_back(v2);
        }
        else if(v1->x <= xr && v2->x <= xr) {
            outList.push_back(v2);
        }
        v1 = v2;
    }
    pd.points = outList;
}
void RectanglePolygonClipper::clipTop(PolygonData& pd, int yt) {
    PointData* v1 = pd.points.at(0);
    std::vector<PointData*> outList;
    for (int i=1; i != 0; (i !=0 && i++)) {
        if (i == pd.points.size()){i = 0;}
        PointData* v2 = pd.points.at(i);
        if(v1->y >= yt && v2->y < yt) {
            int xTemp;
            int yTemp;
            RectangleLineClipper::getHIntersection(v1->x, v1->y, v2->x, v2->y, yt, xTemp, yTemp);
            outList.push_back(new PointData(xTemp, yTemp, pd.color));
        }
        else if(v1->y < yt && v2->y >= yt) {
            int xTemp;
            int yTemp;
            RectangleLineClipper::getHIntersection(v1->x, v1->y, v2->x, v2->y, yt, xTemp, yTemp);
            outList.push_back(new PointData(xTemp, yTemp, pd.color));
            outList.push_back(v2);
        }
        else if(v1->y >= yt && v2->y >= yt) {
            outList.push_back(v2);
        }
        v1 = v2;
    }
    pd.points = outList;
}
void RectanglePolygonClipper::clipBottom(PolygonData& pd, int yb) {
    PointData* v1 = pd.points.at(0);
    std::vector<PointData*> outList;
    for (int i=1; i != 0; (i !=0 && i++)) {
        if (i == pd.points.size()){i = 0;}
        PointData* v2 = pd.points.at(i);
        if(v1->y <= yb && v2->y > yb) {
            int xTemp;
            int yTemp;
            RectangleLineClipper::getHIntersection(v1->x, v1->y, v2->x, v2->y, yb, xTemp, yTemp);
            outList.push_back(new PointData(xTemp, yTemp, pd.color));
        }
        else if(v1->y > yb && v2->y <= yb) {
            int xTemp;
            int yTemp;
            RectangleLineClipper::getHIntersection(v1->x, v1->y, v2->x, v2->y, yb, xTemp, yTemp);
            outList.push_back(new PointData(xTemp, yTemp, pd.color));
            outList.push_back(v2);
        }
        else if(v1->y <= yb && v2->y <= yb) {
            outList.push_back(v2);
        }
        v1 = v2;
    }
    pd.points = outList;
}
