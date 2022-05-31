//
// Created by abdal on 5/29/2022.

#include <cmath>
#include "Rectangle.h"
#include "RectangleData.h"
#include "RectangleDrawer.h"
#include "CardinalSplineData.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>
#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")

Rectangle::Rectangle(int xt, int yt, int xb, int yb, COLORREF color): Shape(new RectangleData(xt, yt, xb, yb, color), new RectangleDrawer()) {
    draw();
}

void DrawHermite(Vector& p1, Vector& T1, Vector& p2, Vector& T2) {
    double a0 = p1[0], a1 = T1[0],
            a2 = -3 * p1[0] - 2 * T1[0] + 3 * p2[0] - T2[0],
            a3 = 2 * p1[0] + T1[0] - 2 * p2[0] + T2[0];
    double b0 = p1[1], b1 = T1[1],
            b2 = -3 * p1[1] - 2 * T1[1] + 3 * p2[1] - T2[1],
            b3 = 2 * p1[1] + T1[1] - 2 * p2[1] + T2[1];
    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t * t, t3 = t2 * t;
        double x = a0 + a1 * t + a2 * t2 + a3 * t3;
        double y = b0 + b1 * t + b2 * t2 + b3 * t3;
        glVertex2d(round(x), round(y));
    }
}

void DrawBezier(Vector& p1, Vector& p2, Vector& p3, Vector& p4) {
    Vector T0(3*(p2[0]-p1[0]),3*(p2[1]-p1[1]));
    Vector T1(3*(p4[0]-p3[0]),3*(p4[1]-p3[1]));
    DrawHermite(p1,T0,p4,T1);
}

void Rectangle::fillWithHermite(){
    cout<<"Filling with Hermite"<<endl;
    RectangleData data = *(RectangleData*)shapeData;
    COLORREF color = data.color;
    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;
    for (int i = data.yt; i < data.yb; ++i) {
        glBegin(GL_POINTS);
        glColor3f(r, g, b);
        Vector T1(3 * ((data.xb-data.xt)/2 - data.xt), 3 * (i - i));
        Vector T2(3 * (data.xb - (data.xb-data.xt)/2), 3 * (i - i));
        Vector p0(data.xt,i);
        Vector p3(data.xb,i);
        DrawHermite(p0,T1,p3,T2);
        glEnd();
        glFlush();
    }
}

void Rectangle::fillWithBezier(){
    cout<<"Filling with Bezier"<<endl;
    RectangleData data = *(RectangleData*)shapeData;
    COLORREF color = data.color;
    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;
    for (int i = data.xt; i < data.xb ; ++i) {
        glBegin(GL_POINTS);
        glColor3f(r, g, b);
        Vector p1(i,data.yt);
        Vector p2(i,(data.yb-data.yt)/2);
        Vector p3(i,(data.yb-data.yt)/2);
        Vector p4(i,data.yb);
        DrawBezier(p1,p2,p3,p4);
        glEnd();
        glFlush();
    }
}

void Rectangle::fill(){
    RectangleData data = *(RectangleData*)shapeData;
    if((data.xb-data.xt)==(data.yb-data.yt)){
        fillWithHermite();
    }
    else{
        fillWithBezier();
    }
}

ostream& Rectangle::format(ostream &out, const Shape &c) {
    RectangleData data = *(RectangleData*) shapeData;
    out<<"rectangle "<<data.xt<<" "<<data.yt<<" "<<data.xb<<" "<<data.yb<<" - "<<((int)GetRValue(data.color))<<" "<<((int)GetGValue(data.color))<<" "<<((int)GetBValue(data.color));
    return out;
}