#include "Ellipse.h"
#include "EllipseData.h"
#include "EllipseDrawerDirect.h"

Ellipse::Ellipse(int x1, int y1, int x2, int y2, int x3, int y3, COLORREF color, EllipseDrawer* drawer = new EllipseDrawerDirect()) : Shape(new EllipseData(x1, y1, x2, y2, x3, y3, color), drawer){
    draw();
}
