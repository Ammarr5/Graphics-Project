#include "LineDrawerDDA.h"
#include "LineData.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")


void LineDrawerDDA::draw(ShapeData* data) {
    LineData lData = *(LineData *) data;
    int x1 = lData.x1;
    int y1 = lData.y1;
    int x2 = lData.x2;
    int y2 = lData.y2;

    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dy) <= abs(dx)) {
        if (x1 > x2) {
            swap(x1, y1, x2, y2);
        }
        int x = x1;
        double y = y1;
        glVertex2d(x, y);
        while (x < x2) {
            x++;
            y += (double) dy / dx;
            glVertex2d(x, Round(y));
        }
    }
    else {
        if (y1 > y2) {
            swap(x1, y1, x2, y2);
        }
        double x = x1;
        int y = y1;
        glVertex2d(x, y);
        while (y < y2) {
            y++;
            x += (double) dx / dy;
            glVertex2d(Round(x), y);
        }
    }
    glEnd();
    glFlush();
}