#include "CardinalSplineDrawer.h"
#include "CardinalSplineData.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>
#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")

int Round(double x)
{
    return (int)(x + 0.5);
}
void DrawHermiteCurve(Vector& p1, Vector& T1, Vector& p2, Vector& T2)
{
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
        glVertex2d(Round(x), Round(y));
    }
}
void CardinalSplineDrawer::draw(ShapeData* data) {
    CardinalSplineData splineData = *(CardinalSplineData *) data;
    Vector* points = splineData.points;
    int n=splineData.n;
    double c=splineData.c;
    COLORREF color = splineData.color;

    float r = (float)GetRValue(color)/255;
    float g = (float)GetGValue(color)/255;
    float b = (float)GetBValue(color)/255;

    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    double c1 = 1 - c;
    Vector T0(c1 * (points[2][0] - points[0][0]), c1 * (points[2][1] - points[0][1]));
    for (int i = 2; i < n - 1; i++)
    {
        Vector T1(c1 * (points[i + 1][0] - points[i - 1][0]), c1 * (points[i + 1][1] - points[i - 1][1]));
        DrawHermiteCurve((points[i - 1]), T0, points[i], T1);
        T0 = T1;
    }
    glEnd();
    glFlush();
}