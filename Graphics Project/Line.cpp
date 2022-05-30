#include "Line.h"
#include "LineData.h"
#include "LineDrawerDDA.h"
Line::Line(int x1, int y1, int x2, int y2, COLORREF color, LineDrawer* drawer = new LineDrawerDDA()) : Shape(new LineData(x1, y1, x2, y2, color), drawer){
    draw();
}

ostream& Line::format(ostream &out, const Shape &c) {
    LineData data = *(LineData*) shapeData;
    out<<"line "<<data.x1<<" "<<data.y1<<" "<<data.x2<<" "<<data.y2<<" - "<<((int)GetRValue(data.color))<<" "<<((int)GetGValue(data.color))<<" "<<((int)GetBValue(data.color));
    return out;
}