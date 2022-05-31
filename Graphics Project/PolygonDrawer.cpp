//
// Created by abdal on 5/30/2022.
//

#include "PolygonDrawer.h"
#include "PolygonData.h"
#include <gl\GLu.h>
#include <utility>
#include <windef.h>
#include <cmath>
#include <list>

#define N 600
#define MAXINT 1e9

using namespace std;

void PolygonDrawer::InitEntries(pair<int, int> *table)
{
    for(int i = 0; i < N; i++)
    {
        table[i].first = MAXINT;
        table[i].second = -MAXINT;
    }
}


void PolygonDrawer::ScanEdge(PointData* v1, PointData* v2, pair<int, int> *table)
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

void PolygonDrawer::DrawSanLines(pair<int, int> *table, COLORREF color)
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

void PolygonDrawer::convexFilling(ShapeData* data)
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

void PolygonDrawer::draw(ShapeData* data) {
    PolygonData pd = *(PolygonData*) data;
    COLORREF color = pd.color;
    std::vector<PointData*> points = pd.points;

    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_LINE_LOOP);
    for(PointData* point : points) {
        glVertex2i(point->x, point->y);
    }
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glFlush();
}

// Non Convex Filling.
struct EdgeRec
{
    double x;
    double minv;
    int ymax;
    bool operator<(EdgeRec r)
    {
        return x<r.x;
    }
};

typedef list<EdgeRec> EdgeList;

EdgeRec InitEdgeRec(PointData*& v1,PointData*& v2)
{
    if(v1->y > v2->y)
        swap(v1,v2);
    EdgeRec rec;
    rec.x = v1->x;
    rec.ymax = v2->y;
    rec.minv = (double)(v2->x - v1->x)/(v2->y - v1->y);
    return rec;
}

void InitEdgeTable(vector<PointData*> polygon, int n, EdgeList table[])
{
    PointData* v1 = polygon[n - 1];
    for(int i = 0; i < n; i++)
    {
        PointData* v2 = polygon[i];
        if(v1->y == v2->y){
            v1 = v2;
            continue;
        }
        EdgeRec rec = InitEdgeRec(v1, v2);
        table[v1->y].push_back(rec);
        v1 = polygon[i];
    }
}

void PolygonDrawer::nonConvexFilling(ShapeData* data) {
    EdgeList *table = new EdgeList[N];
    PolygonData pd = *(PolygonData*) data;
    InitEdgeTable(pd.points, (int)pd.points.size(), table);
    int y = 0;
    while (y < N && table[y].size() == 0)
        y++;
    if(y == N)
        return;

    COLORREF color = pd.color;

    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;

    glBegin(GL_POINTS);
    glColor3f(r, g, b);

    EdgeList ActiveList = table[y];
    while (ActiveList.size() > 0)
    {
        ActiveList.sort();
        for(EdgeList::iterator it = ActiveList.begin(); it != ActiveList.end(); it++)
        {
            int x1=(int)ceil(it->x);
            it++;
            int x2=(int)floor(it->x);
            for(int x = x1; x <= x2; x++)
                glVertex2d(x, y);
        }
        y++;
        EdgeList::iterator it=ActiveList.begin();
        while(it!=ActiveList.end())
            if(y==it->ymax) it=ActiveList.erase(it); else it++;
        for(EdgeList::iterator it=ActiveList.begin();it!=ActiveList.end();it++)
            it->x+=it->minv;
        ActiveList.insert(ActiveList.end(),table[y].begin(),table[y].end());
    }
    glEnd();
    glFlush();
    delete[] table;
}