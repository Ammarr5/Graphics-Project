#include "FilledCircleByLineDrawer.h"
#include "FilledCircleData.h"
#include <iostream>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
using namespace std;

void DrawLine(int x1, int y1, int x2, int y2) {
    for (double t = 0; t <= 1; t += 0.001) {
        int x = x1 + (x2 - x1) * t;
        int y = y1 + (y2 - y1) * t;
        glVertex2d(x, y);
    }
}
void Draw2Lines1(int xc, int yc, int x, int y)
{
    DrawLine(xc,yc,xc - y, yc - x);
    DrawLine(xc,yc,xc - x, yc - y);
}
void Draw2Lines2(int xc, int yc, int x, int y)
{
    DrawLine(xc,yc,xc + y, yc - x);
    DrawLine(xc,yc,xc + x, yc - y);
}
void Draw2Lines3(int xc, int yc, int x, int y)
{
    DrawLine(xc,yc,xc + y, yc + x);
    DrawLine(xc,yc,xc + x, yc + y);
}
void Draw2Lines4(int xc, int yc, int x, int y)
{
    DrawLine(xc,yc,xc - y, yc + x);
    DrawLine(xc,yc,xc - x, yc + y);
}
void FilledCircleByLineDrawer::fill(ShapeData* data){
    FilledCircleData fData = *(FilledCircleData *) data;
    int xc = fData.xc;
    int yc = fData.yc;
    int x = fData.x;
    int y = fData.y;
    int q = fData.q;
    COLORREF color = fData.color;
    double radius= calculateRadius(xc,yc,x,y);
    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;

    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    if(q==1){
        int x1 = 0;
        double y1 = radius;
        Draw2Lines1(xc, yc, 0, radius);
        while (x1 < y1)
        {
            x1++;
            y1 = sqrt((double)radius*radius - x1*x1);
            Draw2Lines1(xc, yc, x1, round(y1));
        }
    }
    else if(q==2){
        int x1 = 0;
        double y1 = radius;
        Draw2Lines2(xc, yc, 0, radius);
        while (x1 < y1)
        {
            x1++;
            y1 = sqrt((double)radius*radius - x1*x1);
            Draw2Lines2(xc, yc, x1, round(y1));
        }
    }
    else if(q==3){
        int x1 = 0;
        double y1 = radius;
        Draw2Lines3(xc, yc, 0, radius);
        while (x1 < y1)
        {
            x1++;
            y1 = sqrt((double)radius*radius - x1*x1);
            Draw2Lines3(xc, yc, x1, round(y1));
        }
    }
    else if(q==4){
        int x1 = 0;
        double y1 = radius;
        Draw2Lines4(xc, yc, 0, radius);
        while (x1 < y1)
        {
            x1++;
            y1 = sqrt((double)radius*radius - x1*x1);
            Draw2Lines4(xc, yc, x1, round(y1));
        }
    }
    glEnd();
    glFlush();
}
void FilledCircleByLineDrawer::draw(ShapeData* data){
    cout<<"Fill Circle quarter by lines Selected."<<endl;
    FilledCircleData fData = *(FilledCircleData *) data;
    int xc = fData.xc;
    int yc = fData.yc;
    int x = fData.x;
    int y = fData.y;
    int q = fData.q;
    COLORREF color = fData.color;
    double radius= calculateRadius(xc,yc,x,y);

    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;

    glBegin(GL_POINTS);
    glColor3f(r, g, b);

    int x1 = 0;
    double y1 = radius;
    Draw8Points(xc, yc, 0, radius);
    while (x1 < y1)
    {
        x1++;
        y1 = sqrt((double)radius*radius - x1*x1);
        Draw8Points(xc, yc, x1, round(y1));
    }
    glEnd();
    glFlush();
    fill(data);
}
