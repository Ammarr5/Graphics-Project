#include "EllipseDrawerMidpoint.h"
#include "EllipseData.h"

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
    double y = RB, x = 0.0, a2 = RA * RA, b2 = RB * RB;
    int d = (int)(b2 - a2 * b + 0.25 * a2);
    Draw4Points(x1, y1, (int)round(x), (int)round(y));
    while (b2 * x <= a2 * y)
    {
        x++;
        if (d > 0)
        {
            y--;
            d += (int)(b2 * (2 * x + 3) + a2 * (-2 * y + 2));
        }
        else
        {
            d += (int)(b2 * (2 * x + 3));
        }
        Draw4Points(x1, y1, (int)round(x), (int)round(y));
    }
    d = (int)((x+0.5) * (x+0.5) * b2 + a2 * (y - 1)*(y-1) - a2 * b2);
    Draw4Points(x1,y1,(int)round(x),(int)round(y));
    while(y!=0)
    {
        y--;
        if (d>0)
        {
            d+=(int)(a2 * (-2*y+3));
        }
        else
        {
            x++;
            d += (int)(b2 *(2*x+2) + a2 * (-2*y+3));
        }
        Draw4Points(x1,y1,(int)round(x),(int)round(y));
    }
    glEnd();
    glFlush();
}