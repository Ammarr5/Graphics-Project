#include "EllipseDrawerMidpoint.h"
#include "EllipseData.h"
#include <cmath>

#include <Windows.h>
#include <gl\GLu.h>
#include <valarray>
#include <iostream>
using namespace std;

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

void EllipseDrawerMidpoint::draw(ShapeData* data)
{
    cout<<"Ellipse Midpoint algorithm selected."<<endl;
    EllipseData ellipseData = *(EllipseData *) data;
    int x1 = ellipseData.x1;
    int y1 = ellipseData.y1;
    int x2 = ellipseData.x2;
    int y2 = ellipseData.y2;
    int x3 = ellipseData.x3;
    int y3 = ellipseData.y3;
    COLORREF color = ellipseData.color;

    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;

    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    int RA = (int)sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    int RB = (int)sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
    double x=0;
    double y=(int)RB;
    double dx=0;
    double dy=(pow(RA,2)*2*RB);
    double d=(int)(pow(RB,2)-(pow(RA,2)*RB)+lround((0.25*pow(RA,2))+0.5));
    Draw4Points(x1,y1,(int)x,(int)y);
    while(dx<dy)
    {
        x++;
        dx+=pow(RB,2)*2;
        if(d<0)
            d+=(dx+pow(RB,2));
        else
        {
            y--;
            dy-=pow(RA,2)*2;
            d+=(dx+pow(RB,2)-dy);
        }
        Draw4Points(x1,y1,(int)x,(int)y);
    }
    d=(int) ((pow(RB,2)*(x+0.5)*(x+0.5))+(pow(RA,2)*pow((y-1),2))-(pow(RA,2)*pow(RB,2)+0.5));
    while(y>0)
    {
        y--;
        dy-=pow(RA,2)*2;
        if(d>=0)
            d+=(pow(RA,2)-dy);
        else
        {
            x++;
            dx+=2*pow(RB,2);
            d+=(dx+pow(RA,2)-dy);
        }
        Draw4Points(x1,y1,(int)x,(int)y);
    }
    glEnd();
    glFlush();
}