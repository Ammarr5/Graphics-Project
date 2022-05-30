#include "Ellipse.h"
#include "EllipseData.h"
#include "EllipseDrawerDirect.h"

Ellipse::Ellipse(int x1, int y1, int x2, int y2, int x3, int y3, COLORREF color, EllipseDrawer* drawer = new EllipseDrawerDirect()) : Shape(new EllipseData(x1, y1, x2, y2, x3, y3, color), drawer){
    draw();
}

ostream& Ellipse::format(ostream &out, const Shape &c) {
    EllipseData data = *(EllipseData*) shapeData;
    out<<"ellipse "<<data.x1<<" "<<data.y1<<" "<<data.x2<<" "<<data.y2<<" "<<data.x3<<" "<<data.y3<<" - "<<((int)GetRValue(data.color))<<" "<<((int)GetGValue(data.color))<<" "<<((int)GetBValue(data.color));
    return out;
}
