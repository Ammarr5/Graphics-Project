#include "EllipseDrawerDirect.h"
#include "EllipseData.h"

#include <Windows.h>
#include <gl\GLu.h>
#include <valarray>

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

void EllipseDrawerDirect::draw(ShapeData* data)
{
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
    int x = 0;
    double y = RB;
    Draw4Points(x1, y1, 0, RB);
    while (x * RB * RB < y * RA * RA)
    {
        x++;
        y = RB* sqrt(1.0 - (double) x * x / (RA * RA));
        Draw4Points(x1, y1, x, (int)round(y));
    }
    int yn = 0;
    double xn = RA;
    Draw4Points(x1, y1, RA, 0);
    while(xn * RB * RB > yn * RA * RA)
    {
        yn++;
        xn = RA * sqrt(1.0 - (double)yn * yn / (RB * RB));
        Draw4Points(x1, y1, (int)round(xn), yn);
    }
}