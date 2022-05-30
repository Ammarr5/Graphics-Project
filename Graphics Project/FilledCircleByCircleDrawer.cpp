#include "FilledCircleByCircleDrawer.h"
#include "FilledCircleData.h"
#include <math.h>
#include <iostream>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")
using namespace std;

void Draw2Points1(int xc, int yc, int x, int y)
{
    glVertex2d(xc - y, yc - x);
    glVertex2d(xc - x, yc - y);
}
void Draw2Points2(int xc, int yc, int x, int y)
{
    glVertex2d(xc + y, yc - x);
    glVertex2d(xc + x, yc - y);
}
void Draw2Points3(int xc, int yc, int x, int y)
{
    glVertex2d(xc + y, yc + x);
    glVertex2d(xc + x, yc + y);
}
void Draw2Points4(int xc, int yc, int x, int y)
{
    glVertex2d(xc - y, yc + x);
    glVertex2d(xc - x, yc + y);
}

void FilledCircleByCircleDrawer::fill(ShapeData * data) {
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
    radius--;
    if(q==1){
        while(radius>0) {
            int x1 = 0;
            double y1 = radius;
            Draw2Points1(xc, yc, 0, radius);
            while (x1 < y1) {
                x1++;
                y1 = sqrt((double) radius * radius - x1 * x1);
                Draw2Points1(xc, yc, x1, round(y1));
            }
            radius--;
        }
    }
    else if(q==2){
        while(radius>0) {
            int x1 = 0;
            double y1 = radius;
            Draw2Points2(xc, yc, 0, radius);
            while (x1 < y1) {
                x1++;
                y1 = sqrt((double) radius * radius - x1 * x1);
                Draw2Points2(xc, yc, x1, round(y1));
            }
            radius--;
        }
    }
    else if(q==3){
        while(radius>0) {
            int x1 = 0;
            double y1 = radius;
            Draw2Points3(xc, yc, 0, radius);
            while (x1 < y1) {
                x1++;
                y1 = sqrt((double) radius * radius - x1 * x1);
                Draw2Points3(xc, yc, x1, round(y1));
            }
            radius--;
        }
    }
    else if(q==4){
        while(radius>0) {
            int x1 = 0;
            double y1 = radius;
            Draw2Points4(xc, yc, 0, radius);
            while (x1 < y1) {
                x1++;
                y1 = sqrt((double) radius * radius - x1 * x1);
                Draw2Points4(xc, yc, x1, round(y1));
            }
            radius--;
        }
    }
    glEnd();
    glFlush();
}

void FilledCircleByCircleDrawer::draw(ShapeData* data){
    cout<<"Fill Circle quarter by circles Selected."<<endl;
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