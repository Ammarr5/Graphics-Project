#include "LineDrawerMidpoint.h"
#include "LineData.h"

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>

#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")

void LineDrawerMidpoint::draw(ShapeData* data) {
    LineData lData = *(LineData *) data;
    int x1 = lData.x1;
    int y1 = lData.y1;
    int x2 = lData.x2;
    int y2 = lData.y2;

    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dy) < abs(dx)) {
        int d = dx - 2 * dy;
        int change1 = 2 * dx - 2 * dy;
        int change2 = -2 * dy;
        if (x1 > x2) {
            swap(x1, y1, x2, y2);
        }
        if (y1 < y2) {
            int x = x1;
            int y = y1;
            glVertex2d(x, y);
            while (x < x2) {
                if (d < 0) {
                    d += change1;
                    y++;
                }
                else {
                    d += change2;
                }
                x++;
                glVertex2d(x, y);
            }
        }
        else {
            int x = x1;
            int y = y1;
            glVertex2d(x, y);
            while (x < x2) {
                if (d < 0) {
                    d += change1;
                    y--;
                }
                else {
                    d += change2;
                }
                x++;
                glVertex2d(x, y);
            }
        }
    }
    else {
        int d = 2 * dx - dy;
        int change1 = 2 * dx - 2 * dy;
        int change2 = 2 * dx;
        if (y1 > y2) {
            swap(x1, y1, x2, y2);
        }
        if (x1 < x2) {
            int x = x1;
            int y = y1;
            glVertex2d(x, y);
            while (y < y2) {
                if (d > 0) {
                    d += change1;
                    x++;
                }
                else {
                    d += change2;
                }
                y++;
                glVertex2d(x, y);
            }
        }
        else {
            int x = x1;
            int y = y1;
            glVertex2d(x, y);
            while (y > y2) {
                if (d > 0) {
                    d += change1;
                    x--;
                }
                else {
                    d += change2;
                }
                y++;
                glVertex2d(x, y);
            }
        }
    }
    glEnd();
    glFlush();
}