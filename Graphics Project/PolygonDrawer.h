//
// Created by abdal on 5/30/2022.
//

#ifndef GRAPHICS_PROJECT_POLYGONDRAWER_H
#define GRAPHICS_PROJECT_POLYGONDRAWER_H


#include "ShapeDrawer.h"
#include "PointData.h"
#include <utility>
using namespace std;

class PolygonDrawer : public ShapeDrawer{
public:
    void draw(ShapeData*);
    void convexFilling(ShapeData*);
    void DrawSanLines(pair<int, int>*, COLORREF);
    void ScanEdge(PointData*, PointData*, pair<int, int>*);
    void InitEntries(pair<int, int>*);
};


#endif //GRAPHICS_PROJECT_POLYGONDRAWER_H
