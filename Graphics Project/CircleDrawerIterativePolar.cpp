#include "CircleDrawerIterativePolar.h"
#include "CircleData.h"

#include <Windows.h>
#include <gl\GLu.h>
#include <valarray>
#include <iostream>
using namespace std;

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

void CircleDrawerIterativePolar::draw(ShapeData* data)
{
    cout<<"Circle Iterative Polar algorithm selected."<<endl;
    CircleData circleData = *(CircleData *) data;
    int x1 = circleData.x1;
    int y1 = circleData.y1;
    int x2 = circleData.x2;
    int y2 = circleData.y2;
    COLORREF color = circleData.color;

    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;

    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    int R = (int)sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    double x = R, y = 0;
    double dTheta = 1.0 / R;
    double cdTheta = cos(dTheta), sdTheta = sin(dTheta);
    Draw8Points(x1, y1, (int)x, (int)y);
    while(x > y)
    {

        y = x * sdTheta + y * cdTheta;
        x = x * cdTheta - y * sdTheta;
        Draw8Points(x1, y1, (int)round(x), (int)round(y));
    }
    glEnd();
    glFlush();
}
