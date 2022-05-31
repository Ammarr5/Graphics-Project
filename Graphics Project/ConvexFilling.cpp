//
// Created by Ziad on 5/30/2022.
//

#include "ConvexFilling.h"
#include "PolygonDrawer.h"
#include "PolygonData.h"
#include <stack>
#include <utility>
#include <windef.h>
#include <GL/glut.h>
#include <cmath>

#define N 600
#define MAXINT 1e9

using namespace std;

void ConvexFilling::InitEntries(pair<int, int> *table)
{
    for(int i = 0; i < N; i++)
    {
        table[i].first = MAXINT;
        table[i].second = -MAXINT;
    }
}


void ConvexFilling::ScanEdge(PointData* v1, PointData* v2, pair<int, int> *table)
{
    if(v1->y == v2->y)
        return;
    if(v1->y > v2->y)
        swap(v1,v2);

    double minv=(double)(v2->x - v1->x) / (v2->y - v1->y);
    double x = v1->x;
    int y = v1->y;
    while(y < v2->y)
    {
        if(x < table[y].first)
            table[y].first=(int)ceil(x);
        if(x > table[y].second)
            table[y].second = (int)floor(x);
        y++;
        x += minv;
    }
}

void ConvexFilling::DrawSanLines(pair<int, int> *table, COLORREF color)
{
    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;

    glBegin(GL_POINTS);
    glColor3f(r, g, b);


    for(int y = 0; y < N; y++)
        if(table[y].first < table[y].second)
            for(int x = table[y].first; x <= table[y].second; x++)
                glVertex2d(x, y);

    glEnd();
    glFlush();
}

void ConvexFilling::draw(ShapeData* data)
{
    PolygonData pd = *(PolygonData*) data;
    COLORREF color = pd.color;
    pair<int, int> *table=new pair<int, int>[N];
    InitEntries(table);
    PointData *v1 = pd.points.back();
    for(int i = 0; i < (int) pd.points.size(); i++)
    {
        PointData *v2 = pd.points[i];
        ScanEdge(v1, v2, table);
        v1 = pd.points[i];
    }
    DrawSanLines(table, color);
    delete table;
}
