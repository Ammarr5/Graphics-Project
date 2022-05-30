#include "Circle.h"
#include "CircleData.h"
#include "CircleDrawerDirect.h"

Circle::Circle(int x1, int y1, int x2, int y2, COLORREF color, CircleDrawer* drawer = new CircleDrawerDirect()) : Shape(new CircleData(x1, y1, x2, y2, color), drawer){
    draw();
}

ostream& Circle::format(ostream &out, const Shape &c) {
    CircleData data = *(CircleData*) shapeData;
    out<<"circle "<<data.x1<<" "<<data.y1<<" "<<data.x2<<" "<<data.y2<<" - "<<((int)GetRValue(data.color))<<" "<<((int)GetGValue(data.color))<<" "<<((int)GetBValue(data.color));
    return out;
}

