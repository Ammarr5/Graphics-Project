#include "LineDrawerParametric.h"
#include "LineData.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")


void LineDrawerParametric::draw(ShapeData* data) {
    LineData lData = *(LineData *) data;
    int x1 = lData.x1;
    int y1 = lData.y1;
    int x2 = lData.x2;
    int y2 = lData.y2;

    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    for (double t = 0; t <= 1; t += 0.001) {
        int x = x1 + (x2 - x1) * t;
        int y = y1 + (y2 - y1) * t;
        glVertex2d(x, y);
    }
    glEnd();
    glFlush();
}