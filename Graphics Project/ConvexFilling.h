//
// Created by Ziad on 5/30/2022.
//

#include <iostream>
#include <utility>
#include <vector>
#include "PolygonDrawer.h"
#include "PolygonData.h"
using namespace std;


class ConvexFilling : public PolygonDrawer{
    vector<pair<int, int>> Entry;
public:
    void draw(ShapeData*);
    void DrawSanLines(pair<int, int>*, COLORREF);
    void ScanEdge(PointData*, PointData*, pair<int, int>*);
    void InitEntries(pair<int, int>*);
};

