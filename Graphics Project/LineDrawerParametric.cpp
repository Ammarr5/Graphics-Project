#include "LineDrawerParametric.h"
#include "LineData.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>
#include <iostream>
using namespace std;

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")


void LineDrawerParametric::draw(ShapeData* data) {
    cout<<"Line Parametric algorithm selected."<<endl;
    LineData lData = *(LineData *) data;
    int x1 = lData.x1;
    int y1 = lData.y1;
    int x2 = lData.x2;
    int y2 = lData.y2;
    COLORREF color = lData.color;

    glBegin(GL_POINTS);
    glColor3f((float)GetRValue(color)/255, (float)GetGValue(color)/255, (float) GetBValue(color)/255);
    for (double t = 0; t <= 1; t += 0.001) {
        int x = x1 + (x2 - x1) * t;
        int y = y1 + (y2 - y1) * t;
        glVertex2d(x, y);
    }
    glEnd();
    glFlush();
}